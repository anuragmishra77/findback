# FindBack

An intelligent Lost & Found system written in modern C++.

## Architecture

Lost Item -> Preprocessing -> NLP Engine -> Similarity Engine -> Candidate Items -> Match Score -> Ranked Results

## Features

- Register lost and found items
- Search and filter items
- Text preprocessing
- TF-IDF vectorization
- Cosine similarity
- Multi-factor match scoring
- Ranked candidate matches
- Simple CLI interface
- Unit-style self tests

## Build

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp src/*.cpp -Iinclude -o findback
./findback
```

## Learning path

The code is intentionally split into small components so we can study C++ concepts incrementally: OOP, STL, file/data modeling, text preprocessing, TF-IDF, vector math, cosine similarity, ranking, testing, and architecture.
