#ifndef HEADLINEMATCH_H
#define HEADLINEMATCH_H

struct HeadlineMatch {
    int headlineId;
    int eventId;
    int groupId;
    double similarity;
    
    HeadlineMatch() : headlineId(-1), eventId(-1), groupId(-1), similarity(0.0) {}
    HeadlineMatch(int headlineId, int eventId, int groupId, double similarity)
        : headlineId(headlineId), eventId(eventId), groupId(groupId), similarity(similarity) {}
};

#endif // HEADLINEMATCH_H




