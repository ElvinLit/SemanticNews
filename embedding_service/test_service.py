"""
Test suite for the embedding service API endpoints
"""
import pytest
import numpy as np
from fastapi.testclient import TestClient
from main import app

client = TestClient(app)


class TestEmbedEndpoint:
    """Tests for the /embed POST endpoint"""
    
    def test_embed_single_text(self):
        """Test embedding a single text"""
        response = client.post(
            "/embed",
            json={"texts": ["Hello world"]}
        )
        assert response.status_code == 200
        data = response.json()
        assert "embeddings" in data
        assert len(data["embeddings"]) == 1
        assert isinstance(data["embeddings"][0], list)
        assert len(data["embeddings"][0]) > 0  # Should have embedding dimensions
    
    def test_embed_multiple_texts(self):
        """Test embedding multiple texts in one request"""
        texts = [
            "Miami Heat vs 76ers",
            "Breaking news today",
            "FastAPI is great for building APIs",
            "Python programming language tutorial",
            "Lebron James vs Stephen Curry",
            "Miami beats Philadelphia in a huge upset",
            "NBA playoffs are starting soon",
            "Basketball reaches an all time high in popularity",
        ]
        response = client.post(
            "/embed",
            json={"texts": texts}
        )
        assert response.status_code == 200
        data = response.json()
        assert "embeddings" in data
        assert len(data["embeddings"]) == len(texts)
        
        # All embeddings should have the same dimension
        embedding_dim = len(data["embeddings"][0])
        for embedding in data["embeddings"]:
            assert len(embedding) == embedding_dim


        print(f"\nMain text: '{texts[0]}'")
        embeddings = data["embeddings"]
        for i in range(1, len(texts) - 1):
            similarity = np.dot(embeddings[0], np.array(embeddings[i]))
            print(f"Text: '{texts[i]}' Similarity: {similarity:.4f}")
    
    def test_embed_empty_list(self):
        """Test that empty texts list returns 400 error"""
        response = client.post(
            "/embed",
            json={"texts": []}
        )
        assert response.status_code == 400
        data = response.json()
        assert "detail" in data
        assert "cannot be empty" in data["detail"].lower()
    
    def test_embed_missing_texts_field(self):
        """Test that missing texts field returns validation error"""
        response = client.post(
            "/embed",
            json={}
        )
        assert response.status_code == 422  # FastAPI validation error
    
    def test_embed_normalized_embeddings(self):
        """Test that embeddings are normalized (unit length)"""
        response = client.post(
            "/embed",
            json={"texts": ["Test normalization"]}
        )
        assert response.status_code == 200
        data = response.json()
        embedding = data["embeddings"][0]
        
        # Compute L2 norm using numpy (faster)
        emb_array = np.array(embedding)
        norm = np.linalg.norm(emb_array)
        
        # Should be approximately 1.0 (normalized)
        assert abs(norm - 1.0) < 0.01, f"Embedding not normalized, norm={norm}"
    
    def test_embed_similar_texts_have_similar_embeddings(self):
        """Test that similar texts produce similar embeddings"""
        similar_texts = [
            "Miami Heat basketball game",
            "Miami Heat vs 76ers basketball"
        ]
        response = client.post(
            "/embed",
            json={"texts": similar_texts}
        )
        assert response.status_code == 200
        data = response.json()
        emb1 = data["embeddings"][0]
        emb2 = data["embeddings"][1]
        
        # Compute cosine similarity (dot product since normalized) using numpy (faster)
        emb1_array = np.array(emb1)
        emb2_array = np.array(emb2)
        similarity = np.dot(emb1_array, emb2_array)
        
        # Print similarity score
        print(f"\nSimilarity score: {similarity:.4f}")
        print(f"Text 1: '{similar_texts[0]}'")
        print(f"Text 2: '{similar_texts[1]}'")
        
        # Similar texts should have high similarity (> 0.7)
        assert similarity > 0.7, f"Similar texts should have high similarity, got {similarity}"
    
    def test_embed_different_texts_have_different_embeddings(self):
        """Test that very different texts produce different embeddings"""
        different_texts = [
            "Miami Heat basketball game",
            "Python programming language tutorial"
        ]
        response = client.post(
            "/embed",
            json={"texts": different_texts}
        )
        assert response.status_code == 200
        data = response.json()
        emb1 = data["embeddings"][0]
        emb2 = data["embeddings"][1]
        
        # Compute cosine similarity
        similarity = sum(a * b for a, b in zip(emb1, emb2))
        
        print(f"\nSimilarity score: {similarity:.4f}")
        print(f"Text 1: '{different_texts[0]}'")
        print(f"Text 2: '{different_texts[1]}'")


        # Different texts should have lower similarity (< 0.5)
        assert similarity < 0.5, f"Different texts should have low similarity, got {similarity}"


class TestHealthEndpoint:
    """Tests for the /health GET endpoint"""
    
    def test_health_check_success(self):
        """Test that health endpoint returns 200 when service is healthy"""
        response = client.get("/health")
        assert response.status_code == 200
        data = response.json()
        assert data["status"] == "ok"

