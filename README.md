# FindBack

**FindBack** is an educational C++17 intelligent Lost & Found matching system.

It demonstrates how a lost-item description can be converted into numerical features and compared against found items using classical NLP.

## Architecture

```
Lost Item
   |
   v
Text Preprocessing
   |
   v
TF-IDF Vectorization
   |
   v
Cosine Similarity
   |
   v
Candidate Items
   |
   v
Match Engine
   |
   v
Weighted Match Score
   |
   v
Ranked Results
```

## Current features

- Lost/found item data model
- Text normalization and tokenization
- Stop-word removal
- Educational stemming
- TF-IDF vectorization
- Cosine similarity
- Candidate filtering by type/status
- Location, category and date signals
- Explainable weighted match score
- Ranked candidate results
- Self-tests
- CMake build support
- No third-party NLP library required

## Match score

The current educational ranking formula is:

```
score =
    0.70 * text_similarity
  + 0.15 * location_similarity
  + 0.10 * category_similarity
  + 0.05 * date_similarity
```

The weights are intentionally simple and explainable. They are not machine-learned weights.

## Build with g++

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp src/*.cpp -Iinclude -o findback
```

Run the demo:

```bash
./findback
```

Run self-tests:

```bash
./findback --test
```

## Build with CMake

```bash
cmake -S . -B build
cmake --build build
./build/findback
./build/findback --test
```

## Project structure

```
findback/
├── include/
│   ├── Item.h
│   ├── TextPreprocessor.h
│   ├── TfidfVectorizer.h
│   ├── SimilarityEngine.h
│   └── MatchEngine.h
├── src/
│   ├── Item.cpp
│   ├── TextPreprocessor.cpp
│   ├── TfidfVectorizer.cpp
│   ├── SimilarityEngine.cpp
│   └── MatchEngine.cpp
├── main.cpp
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Learning roadmap

We will study the project incrementally:

1. C++ structs/classes and enums
2. Header/source separation
3. STL containers
4. Text preprocessing
5. Tokenization and normalization
6. TF, IDF and TF-IDF
7. Vectors and cosine similarity
8. Candidate filtering
9. Match-score design
10. Sorting and ranking
11. Testing and debugging
12. Architecture and future persistence

## Important limitation

This version is the **intelligent matching core + CLI demonstration**. It intentionally does not yet contain user authentication, a database, a full CRUD CLI, or a web frontend. Those can be added after the matching engine is understood.

## Future extensions

- Persistent storage with SQLite
- User accounts and claims
- Full CRUD CLI
- Better date/location matching
- Better stemming/tokenization
- Precision/recall evaluation on a labeled dataset
- Image-based item matching
- REST API and web frontend

The goal is to keep each extension understandable so the implementation can be studied rather than treated as a black box.
