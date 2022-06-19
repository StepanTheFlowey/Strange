#pragma once

#include "Scene.hpp"
#include <SFML\Graphics.hpp>

using BlockPos = sf::Vector2<uint16_t>;
using TxPos = sf::Vector2<uint16_t>;

class SceneMinecraft : public Scene {
  struct Block {
    std::wstring name;
    TxPos txPos;
    uint16_t breakTime;
  };

  struct BlockRenderInfo {
    std::size_t id;
    sf::Vertex vt[4];
  };

  static Block blocks[];
  static const uint16_t blocksCount;

  sf::VertexBuffer vbo_;
  sf::Texture* tileset_;

  std::vector<BlockRenderInfo> renderInfo;

  BlockPos size;
  uint32_t blockTotal;
  uint16_t verticalOffset;
public:

  SceneMinecraft();

  virtual void run() override;
private:

  void setBlock(const BlockPos pos, const uint16_t id);

  void updateBlock(const BlockPos pos);
};