from fastapi import FastAPI, HTTPException, status
import uvicorn
import logging

from sentence_transformers import SentenceTransformer, util

from models import EmbedRequest, EmbedResponse

# Configure logger
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)

app = FastAPI()

model_name = "all-MiniLM-L6-v2"
encoder = SentenceTransformer(model_name)
logger.info("Model loaded successfully")


@app.post("/embed", response_model=EmbedResponse, status_code=status.HTTP_200_OK)
def embed(req: EmbedRequest):
    logger.info(f"Received embedding request for {len(req.texts)} text(s)")
    
    # Validate input
    if not req.texts or len(req.texts) == 0:
        logger.warning("Empty texts list received")
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="texts list cannot be empty"
        )
    
    try:
        logger.debug(f"Encoding {len(req.texts)} texts")
        embeddings = encoder.encode(req.texts, convert_to_tensor=True)
        embeddings = util.normalize_embeddings(embeddings) # divide by l2 norm
        
        embeddings_list = embeddings.tolist()
        
        logger.info(f"Successfully generated {len(embeddings_list)} embeddings")
        return {"embeddings": embeddings_list}
        
    except Exception as e:
        logger.error(f"Failed to generate embeddings: {str(e)}", exc_info=True)
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"Failed to generate embeddings: {str(e)}"
        )

@app.get("/health", status_code=status.HTTP_200_OK)
def health():
    logger.debug("Health check requested")
    
    if encoder is None:
        logger.error("Health check failed: Model not loaded")
        raise HTTPException(
            status_code=status.HTTP_503_SERVICE_UNAVAILABLE,
            detail="Model not loaded"
        )

    try:
        test_embedding = encoder.encode("Hello, world!")
        if test_embedding is None:
            logger.error("Health check failed: Model encoding returned None")
            raise HTTPException(
                status_code=status.HTTP_503_SERVICE_UNAVAILABLE,
                detail="Failed to encode test text"
            )
    except HTTPException:
        raise
    except Exception as e:
        logger.error(f"Health check failed: {str(e)}", exc_info=True)
        raise HTTPException(
            status_code=status.HTTP_503_SERVICE_UNAVAILABLE,
            detail=f"Model health check failed: {str(e)}"
        )

    logger.debug("Health check passed")
    return {"status": "ok"}

if __name__ == "__main__":
    logger.info("Starting embedding service on http://127.0.0.1:8000")
    uvicorn.run(app, host="127.0.0.1", port=8000)
