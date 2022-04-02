#include "SceneMinecraft.hpp"

SceneMinecraft::Block SceneMinecraft::blocks[64]{};
const uint16_t SceneMinecraft::blocksCount = 64;

SceneMinecraft::SceneMinecraft() {
  size.x = sf::VideoMode::getDesktopMode().width / 64;
  size.y = sf::VideoMode::getDesktopMode().height / 64;
  blockTotal = size.x * size.y;

  verticalOffset = sf::VideoMode::getDesktopMode().height % 64;

  vbo_.setPrimitiveType(sf::Quads);
  vbo_.setUsage(sf::VertexBuffer::Stream);
  vbo_.create(blockTotal * 4 + 4);

  renderInfo.resize(blockTotal + 1);

  for(uint16_t i = 0; i < size.x; ++i) {
    for(uint16_t j = 0; j < size.y; ++j) {
      BlockRenderInfo& block = renderInfo[static_cast<size_t>(i) + static_cast<size_t>(j) * size.x];
      block.vt[0].color = sf::Color::White;
      block.vt[1].color = sf::Color::White;
      block.vt[2].color = sf::Color::White;
      block.vt[3].color = sf::Color::White;

      block.vt[0].position.x = i * 64;
      block.vt[0].position.y = j * 64 + verticalOffset;

      block.vt[1].position.x = i * 64;
      block.vt[1].position.y = j * 64 + 64 + verticalOffset;

      block.vt[2].position.x = i * 64 + 64;
      block.vt[2].position.y = j * 64 + 64 + verticalOffset;

      block.vt[3].position.x = i * 64 + 64;
      block.vt[3].position.y = j * 64 + verticalOffset;
      updateBlock(BlockPos(i, j));
    }
  }

  for(uint8_t i = 0; i < 8; ++i) {
    for(uint8_t j = 0; j < 8; ++j) {
      blocks[i + j * 8].txPos = sf::Vector2<uint8_t>(i, j);
    }
  }
}

void SceneMinecraft::run() {
  tileset_ = context->getTexture(IDB_IMG3);

  uint16_t selectedBlock = 0;
  while(context->alive()) {
    context->autoClock();

    context->window.clear(sf::Color::Transparent);
    context->window.draw(vbo_, tileset_);
    context->window.display();

    while(context->pollEvent()) {
      switch(context->event.type) {
        case sf::Event::Closed:
          context->window.close();
          break;
        case sf::Event::MouseMoved:
        {
          const sf::Vector2i mousePos(context->event.mouseMove.x, context->event.mouseMove.y);
          renderInfo[blockTotal].vt[0].position = sf::Vector2f(mousePos) + sf::Vector2f(16, -40);
          renderInfo[blockTotal].vt[1].position = sf::Vector2f(mousePos) + sf::Vector2f(16, -8);
          renderInfo[blockTotal].vt[2].position = sf::Vector2f(mousePos) + sf::Vector2f(48, -8);
          renderInfo[blockTotal].vt[3].position = sf::Vector2f(mousePos) + sf::Vector2f(48, -40);
          updateBlock(BlockPos(size.x, size.y - 1));
          break;
        }
        case sf::Event::MouseWheelScrolled:
          selectedBlock += context->event.mouseWheelScroll.delta;
          if(selectedBlock >= blocksCount) {
            selectedBlock = 0;
          }
          debug(selectedBlock << L'\t' << context->event.mouseWheelScroll.delta);
          setBlock(BlockPos(size.x, size.y - 1), selectedBlock);
          break;
        case sf::Event::MouseButtonPressed:
        {
          sf::Vector2i mousePos(context->event.mouseButton.x, context->event.mouseButton.y);
          mousePos -= sf::Vector2i(0, verticalOffset);
          mousePos.x /= 64;
          mousePos.y /= 64;
          setBlock(BlockPos(mousePos), selectedBlock);
          break;
        }
      }
    }
  }
}

void SceneMinecraft::setBlock(const BlockPos pos, const uint16_t id) {
  const size_t index = static_cast<size_t>(pos.x) + static_cast<size_t>(pos.y) * size.x;
  renderInfo[index].vt[0].texCoords = sf::Vector2f(blocks[id].txPos) + sf::Vector2f(0, 0);
  renderInfo[index].vt[0].texCoords.x *= 16;
  renderInfo[index].vt[0].texCoords.y *= 16;
  renderInfo[index].vt[1].texCoords = sf::Vector2f(blocks[id].txPos) + sf::Vector2f(0, 1);
  renderInfo[index].vt[1].texCoords.x *= 16;
  renderInfo[index].vt[1].texCoords.y *= 16;
  renderInfo[index].vt[2].texCoords = sf::Vector2f(blocks[id].txPos) + sf::Vector2f(1, 1);
  renderInfo[index].vt[2].texCoords.x *= 16;
  renderInfo[index].vt[2].texCoords.y *= 16;
  renderInfo[index].vt[3].texCoords = sf::Vector2f(blocks[id].txPos) + sf::Vector2f(1, 0);
  renderInfo[index].vt[3].texCoords.x *= 16;
  renderInfo[index].vt[3].texCoords.y *= 16;
  vbo_.update(renderInfo[index].vt, 4, index * 4);
}

void SceneMinecraft::updateBlock(const BlockPos pos) {
  const size_t index = static_cast<size_t>(pos.x) + static_cast<size_t>(pos.y) * size.x;
  vbo_.update(renderInfo[index].vt, 4, index * 4);
}
