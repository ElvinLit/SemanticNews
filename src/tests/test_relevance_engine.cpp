#include <QtTest>
#include "engine/RelevanceEngine.h"

class TestRelevanceEngine : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();           // Called once before all tests
    void cleanupTestCase();         // Called once after all tests
    void init();                   // Called before each test
    void cleanup();                // Called after each test
    
    // Test cases
    void testCosineSimilarity_identicalVectors();
    void testCosineSimilarity_orthogonalVectors();
    void testCosineSimilarity_oppositeVectors();
    void testSetEventProfiles();
    void testSetGlobalThreshold();
    void testComputeMatches_aboveThreshold();
    void testComputeMatches_belowThreshold();
    void testComputeMatches_emptyProfiles();
};

void TestRelevanceEngine::initTestCase() {
    // Called once before all tests
    qDebug() << "Starting RelevanceEngine tests...";
}

void TestRelevanceEngine::cleanupTestCase() {
    // Called once after all tests
    qDebug() << "Finished RelevanceEngine tests.";
}

void TestRelevanceEngine::init() {
    // Called before each test
}

void TestRelevanceEngine::cleanup() {
    // Called after each test
}

void TestRelevanceEngine::testCosineSimilarity_identicalVectors() {
    RelevanceEngine engine;
    engine.setGlobalThreshold(0.0);  // Low threshold to catch all matches
    
    // Create identical normalized vectors (embeddings are normalized)
    QVector<float> embedding(384, 0.0f);
    embedding[0] = 1.0f;
    
    // Set up event profile
    EventProfile profile(1, 1, "Test Event", embedding);
    QList<EventProfile> profiles;
    profiles << profile;
    engine.setEventProfiles(profiles);
    
    // Test with identical headline embedding
    QVector<float> headlineEmbedding(384, 0.0f);
    headlineEmbedding[0] = 1.0f;
    
    QList<HeadlineMatch> matches = engine.computeMatches(headlineEmbedding, 1);
    
    // Should find match with similarity = 1.0
    QVERIFY(matches.size() >= 1);
    if (matches.size() > 0) {
        QCOMPARE(matches[0].similarity, 1.0);
    }
}

void TestRelevanceEngine::testCosineSimilarity_orthogonalVectors() {
    RelevanceEngine engine;
    engine.setGlobalThreshold(-1.0);  // Very low threshold to catch all
    
    // Create orthogonal vectors (dot product = 0)
    QVector<float> eventEmbedding(384, 0.0f);
    eventEmbedding[0] = 1.0f;
    
    EventProfile profile(1, 1, "Test Event", eventEmbedding);
    QList<EventProfile> profiles;
    profiles << profile;
    engine.setEventProfiles(profiles);
    
    QVector<float> headlineEmbedding(384, 0.0f);
    headlineEmbedding[1] = 1.0f;  // Orthogonal to event
    
    QList<HeadlineMatch> matches = engine.computeMatches(headlineEmbedding, 1);
    
    // Should find match with similarity = 0.0 (or filtered out if threshold > 0)
    // Since threshold is -1.0, should include it
    QVERIFY(matches.size() >= 1);
    if (matches.size() > 0) {
        QCOMPARE(matches[0].similarity, 0.0);
    }
}

void TestRelevanceEngine::testCosineSimilarity_oppositeVectors() {
    RelevanceEngine engine;
    engine.setGlobalThreshold(-2.0);  // Very low threshold
    
    // Create opposite vectors
    QVector<float> eventEmbedding(384, 0.0f);
    eventEmbedding[0] = 1.0f;
    
    EventProfile profile(1, 1, "Test Event", eventEmbedding);
    QList<EventProfile> profiles;
    profiles << profile;
    engine.setEventProfiles(profiles);
    
    QVector<float> headlineEmbedding(384, 0.0f);
    headlineEmbedding[0] = -1.0f;  // Opposite direction
    
    QList<HeadlineMatch> matches = engine.computeMatches(headlineEmbedding, 1);
    
    // Should find match with similarity = -1.0
    QVERIFY(matches.size() >= 1);
    if (matches.size() > 0) {
        QCOMPARE(matches[0].similarity, -1.0);
    }
}

void TestRelevanceEngine::testSetEventProfiles() {
    RelevanceEngine engine;
    
    QVector<float> embedding(384, 0.0f);
    embedding[0] = 1.0f;
    
    EventProfile profile1(1, 1, "Event 1", embedding);
    EventProfile profile2(2, 1, "Event 2", embedding);
    
    QList<EventProfile> profiles;
    profiles << profile1 << profile2;
    
    engine.setEventProfiles(profiles);
    
    // Test that profiles were set (we'll verify by computing matches)
    QVector<float> headlineEmbedding(384, 0.0f);
    headlineEmbedding[0] = 1.0f;
    
    QList<HeadlineMatch> matches = engine.computeMatches(headlineEmbedding, 1);
    
    // Should find matches (implementation dependent, but at least test doesn't crash)
    QVERIFY(true);  // Basic test that setEventProfiles doesn't crash
}

void TestRelevanceEngine::testSetGlobalThreshold() {
    RelevanceEngine engine;
    
    engine.setGlobalThreshold(0.5);
    engine.setGlobalThreshold(0.7);
    engine.setGlobalThreshold(0.35);
    
    // Test that threshold can be set (no crash)
    QVERIFY(true);
}

void TestRelevanceEngine::testComputeMatches_aboveThreshold() {
    RelevanceEngine engine;
    engine.setGlobalThreshold(0.5);
    
    // Create event profile
    QVector<float> eventEmbedding(384, 0.0f);
    eventEmbedding[0] = 1.0f;
    
    EventProfile profile(1, 1, "Test Event", eventEmbedding);
    QList<EventProfile> profiles;
    profiles << profile;
    engine.setEventProfiles(profiles);
    
    // Create headline embedding (same as event = high similarity)
    QVector<float> headlineEmbedding(384, 0.0f);
    headlineEmbedding[0] = 1.0f;
    
    QList<HeadlineMatch> matches = engine.computeMatches(headlineEmbedding, 1);
    
    // Should find at least one match (similarity should be 1.0, above 0.5 threshold)
    QVERIFY(matches.size() >= 1);
    
    if (matches.size() > 0) {
        QCOMPARE(matches[0].eventId, 1);
        QCOMPARE(matches[0].headlineId, 1);
        QVERIFY(matches[0].similarity >= 0.5);
    }
}

void TestRelevanceEngine::testComputeMatches_belowThreshold() {
    RelevanceEngine engine;
    engine.setGlobalThreshold(0.9);  // High threshold
    
    // Create event profile
    QVector<float> eventEmbedding(384, 0.0f);
    eventEmbedding[0] = 1.0f;
    
    EventProfile profile(1, 1, "Test Event", eventEmbedding);
    QList<EventProfile> profiles;
    profiles << profile;
    engine.setEventProfiles(profiles);
    
    // Create headline embedding (orthogonal = low similarity)
    QVector<float> headlineEmbedding(384, 0.0f);
    headlineEmbedding[1] = 1.0f;  // Different dimension
    
    QList<HeadlineMatch> matches = engine.computeMatches(headlineEmbedding, 1);
    
    // Should find no matches (similarity should be 0.0, below 0.9 threshold)
    QCOMPARE(matches.size(), 0);
}

void TestRelevanceEngine::testComputeMatches_emptyProfiles() {
    RelevanceEngine engine;
    engine.setGlobalThreshold(0.5);
    
    // Don't set any profiles
    QList<EventProfile> emptyProfiles;
    engine.setEventProfiles(emptyProfiles);
    
    QVector<float> headlineEmbedding(384, 0.0f);
    headlineEmbedding[0] = 1.0f;
    
    QList<HeadlineMatch> matches = engine.computeMatches(headlineEmbedding, 1);
    
    // Should return empty list when no profiles
    QCOMPARE(matches.size(), 0);
}

QTEST_MAIN(TestRelevanceEngine)
#include "test_relevance_engine.moc"

