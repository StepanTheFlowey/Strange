#pragma once

#include "Scene.hpp"
#include <SFML\Graphics.hpp>

#define MINECRAFT_BLOCK_SIZE 32

class SceneMinecraft : public Scene {
public:

  SceneMinecraft();

  virtual void run() override;
private:

  using BlockPos = sf::Vector2<uint16_t>;
  using TxPos = sf::Vector2<uint16_t>;

  struct Block {
    enum class Type : uint8_t {
      Null = 0,
      Static,
      States,
      Gui
    };

    enum class Gui : uint8_t {
      Null = 0,
      Workbench,
      Furnace,
      Chest
    };

    std::wstring name;
    TxPos txPos;
    uint16_t breakTime = 0;
    size_t dropId = 0;
    Block::Gui gui = Block::Gui::Null;
  };

  struct BlockRenderInfo {
    size_t id = 0;
    sf::Vertex vt[4];
  };

  const static Block blocks[];

  sf::VertexBuffer vbo_;
  sf::Texture* tileset_ = nullptr;

  std::vector<BlockRenderInfo> renderInfo;

  BlockPos size;
  uint32_t blockTotal;
  uint16_t verticalOffset;

  void setBlock(const BlockPos pos, const uint16_t id);

  void updateBlock(const BlockPos pos);
};