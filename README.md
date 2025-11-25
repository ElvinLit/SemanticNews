# Event News Monitor

A locally-hosted, low-latency desktop application that monitors RSS/Atom feeds and matches headlines to user-defined events using semantic similarity.

## System Design

### Architecture

- **Qt 6.x (C++)**: Desktop application with minimal UI
- **FastAPI (Python)**: Local embedding service running on port 8000
- **SQLite3**: Local database for persistence
- **Sentence-transformers**: Local LLM encoder for embeddings
- **Cosine Similarity**: Relevance matching algorithm

### Components

1. **DataStore**: SQLite database operations (groups, events, headlines, relevance)
2. **RSSFetcher**: Fetches and parses RSS/Atom feeds periodically
3. **EmbeddingClient**: HTTP client for Python embedding service
4. **RelevanceEngine**: Computes cosine similarity between headline and event embeddings
5. **MonitorWorker**: Background thread for processing headlines
6. **UI Components**:
   - LandingPageWidget: Start/continue monitor, clear history
   - EventBuilderWidget: Create and manage groups/events
   - MonitorWidget: Display recent and relevant headlines

### Data Models

- **Group**: User-defined category (e.g., "Sports", "Politics")
- **Event**: Specific event within a group (e.g., "Miami Heat vs 76ers")
- **Headline**: RSS feed item with title, URL, source, timestamps
- **HeadlineMatch**: Relevance match between headline and event (similarity score)

### Workflow

1. User creates groups and events
2. Application fetches RSS feeds periodically
3. New headlines are sent to embedding service
4. Event embeddings are pre-computed
5. Cosine similarity computed for each headline-event pair
6. Matches above threshold are stored and displayed

## Build Requirements

- Qt 6.x (Core, Widgets, Network, Sql, Xml)
- CMake 3.16+
- C++17 compiler
- Python 3.10+ (for embedding service)
- SQLite3

## Configuration

See `config.json` for:
- RSS feed URLs
- Embedding service URL
- Poll interval
- Similarity threshold
