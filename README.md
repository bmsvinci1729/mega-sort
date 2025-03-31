# Performance Comparison: Single Thread vs Multi-Thread

This table compares the execution time for processing different text sizes using single-threaded and multi-threaded approaches.

| **TEXT SIZE**  | **Single Thread**  | **Multi Thread**  |
|---------------|-------------------|------------------|
| 1M           | 1.3s               | 0.148s           |
| 10M          | 14s                | 1.5s             |
| 100M         | 223s               | 54s              |
| 1.7GB (~1B)  | ~30 to 35 min      | 454s (~7.5 min)  |

### Observations:
- Multi-threading significantly reduces execution time.
- The performance gain is more noticeable with larger text sizes.
- The improvement is nearly **10x for small data** and remains considerable even for large datasets.

This highlights the importance of parallel processing for handling large-scale text data efficiently.

Several other improvements could be impplemented by optimizing threads to bring down the execution time much lesser
