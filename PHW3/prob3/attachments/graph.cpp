#include "graph.hpp"

template <typename T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<>>;
struct HeapEntry
{
  std::size_t vertex;
  std::int64_t dist;

  auto operator<=>(const HeapEntry &rhs) const { return dist <=> rhs.dist; }
};

auto Graph::dijkstra(VertexID source) const -> std::vector<Weight>
{
  // FIXME: This is a naive O(V^2) implementation. Overwrite it to make it run
  // within O(ElogV) time, which is more efficient when E = o(V^2/logV).
  std::vector<Weight> dist(numVertices(), infinity);
  std::vector<bool> done(numVertices(), false);
  dist[source] = 0;
  MinHeap<HeapEntry> minheap;

  minheap.push({.vertex = source, .dist = 0});

  while (!minheap.empty())
  {
    VertexID current = minheap.top().vertex;
    done[current] = true;

    for (auto [to, weight] : mAdjacent[current])
    {
      if (!done[to] && dist[current] + weight < dist[to])
      {
        dist[to] = dist[current] + weight;
        minheap.push({.vertex = to, .dist = dist[to]});
      }
    }
    minheap.pop();
  }
  return dist;
}

auto Graph::bellmanFord(VertexID source) const
    -> std::optional<std::vector<Weight>>
{
  // TODO: Implement this.
  std::vector<Weight> dist(numVertices(), infinity);
  dist[source] = 0;

  for (VertexID j = 1; j != numVertices(); ++j)
    for (VertexID i = 0; i != numVertices(); ++i)
    {
      for (auto [to, weight] : mAdjacent[i])
        if (dist[i] != infinity && dist[i] + weight < dist[to])
          dist[to] = dist[i] + weight;
    }

  for (VertexID i = 0; i != numVertices(); ++i)
  {
    for (auto [to, weight] : mAdjacent[i])
      if (dist[i] != infinity && dist[i] + weight < dist[to])
        return std::nullopt;
  }
  return dist;
}