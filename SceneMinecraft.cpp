#include "SceneMinecraft.hpp"

const SceneMinecraft::Block SceneMinecraft::blocks[]{
  { L"Air",              TxPos(0,0),  0    },
  { L"Stone",            TxPos(1,0),  1000 },
  { L"Granite",          TxPos(2,0),  1000 },
  { L"Polished granite", TxPos(3,0),  0    },
  { L"Diorite",          TxPos(4,0),  0    },
  { L"Polished diorite", TxPos(5,0),  0    },
  { L"Andesit",          TxPos(6,0),  0    },
  { L"Polished andesit", TxPos(7,0),  0    },
  { L"Grass",            TxPos(8,0),  0    },
  { L"Dirt",             TxPos(9,0),  0    },
  { L"Polished dirt",    TxPos(10,0), 0    },
  { L"Podzol",           TxPos(11,0), 0    },
  { L"Cobblestone",      TxPos(12,0), 0    },
  { L"Oak planks",       TxPos(13,0), 0    },
  { L"Polished andesit", TxPos(14,0), 0    },
  { L"Polished andesit", TxPos(15,0), 0    }
};

SceneMinecraft::SceneMinecraft() {
  size.x = sf::VideoMode::getDesktopMode().width / MINECRAFT_BLOCK_SIZE;
  size.y = sf::VideoMode::getDesktopMode().height / MINECRAFT_BLOCK_SIZE;
  blockTotal = size.x * size.y;

  verticalOffset = sf::VideoMode::getDesktopMode().height % MINECRAFT_BLOCK_SIZE;

  vbo_.setPrimitiveType(sf::Quads);
  vbo_.setUsage(sf::VertexBuffer::Stream);
  vbo_.create(blockTotal * 4 + 4);

  renderInfo.resize(blockTotal + 1);

  for(uint_fast16_t i = 0; i < size.x; ++i) {
    for(uint_fast16_t j = 0; j < size.y; ++j) {
      BlockRenderInfo& block = renderInfo[static_cast<size_t>(i) + static_cast<size_t>(j) * size.x];

      block.vt[0].color = sf::Color::White;
      block.vt[1].color = sf::Color::White;
      block.vt[2].color = sf::Color::White;
      block.vt[3].color = sf::Color::White;

      block.vt[0].position.x = i * MINECRAFT_BLOCK_SIZE;
      block.vt[0].position.y = j * MINECRAFT_BLOCK_SIZE + verticalOffset;

      block.vt[1].position.x = i * MINECRAFT_BLOCK_SIZE;
      block.vt[1].position.y = j * MINECRAFT_BLOCK_SIZE + MINECRAFT_BLOCK_SIZE + verticalOffset;

      block.vt[2].position.x = i * MINECRAFT_BLOCK_SIZE + MINECRAFT_BLOCK_SIZE;
      block.vt[2].position.y = j * MINECRAFT_BLOCK_SIZE + MINECRAFT_BLOCK_SIZE + verticalOffset;

      block.vt[3].position.x = i * MINECRAFT_BLOCK_SIZE + MINECRAFT_BLOCK_SIZE;
      block.vt[3].position.y = j * MINECRAFT_BLOCK_SIZE + verticalOffset;

      setBlock(BlockPos(i, j), 0);
    }
  }
}

void SceneMinecraft::run() {
  tileset_ = context->getTexture(ID_IMG3);

  uint16_t selectedBlock = 1;
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
          selectedBlock += static_cast<int>(context->event.mouseWheelScroll.delta) % 2;
          if(selectedBlock >= 16) selectedBlock = 16 - 1;
          if(selectedBlock == 0)           selectedBlock = 1;
          debug(selectedBlock << L'\t' << context->event.mouseWheelScroll.delta);
          setBlock(BlockPos(size.x, size.y - 1), selectedBlock);
          break;
        case sf::Event::MouseButtonPressed:
        {
          sf::Vector2i mousePos(context->event.mouseButton.x, context->event.mouseButton.y);
          mousePos -= sf::Vector2i(0, verticalOffset);
          mousePos.x /= MINECRAFT_BLOCK_SIZE;
          mousePos.y /= MINECRAFT_BLOCK_SIZE;
          setBlock(BlockPos(mousePos), selectedBlock);
          break;
        }
      }
    }
  }
}

void SceneMinecraft::setBlock(const BlockPos pos, const uint16_t id) {
  const size_t index = static_cast<size_t>(pos.x) + static_cast<size_t>(pos.y) * size.x;

  renderInfo[index].vt[0].texCoords = sf::Vector2f(blocks[id].txPos) + sf::Vector2f(0.F, 0.F);
  renderInfo[index].vt[0].texCoords *= 16.F;
  renderInfo[index].vt[1].texCoords = sf::Vector2f(blocks[id].txPos) + sf::Vector2f(0.F, 1.F);
  renderInfo[index].vt[1].texCoords *= 16.F;
  renderInfo[index].vt[2].texCoords = sf::Vector2f(blocks[id].txPos) + sf::Vector2f(1.F, 1.F);
  renderInfo[index].vt[2].texCoords *= 16.F;
  renderInfo[index].vt[3].texCoords = sf::Vector2f(blocks[id].txPos) + sf::Vector2f(1.F, 0.F);
  renderInfo[index].vt[3].texCoords *= 16.F;

  vbo_.update(renderInfo[index].vt, 4, index * 4);
}

void SceneMinecraft::updateBlock(const BlockPos pos) {
  const size_t index = static_cast<size_t>(pos.x) + static_cast<size_t>(pos.y) * size.x;
  vbo_.update(renderInfo[index].vt, 4, index * 4);
}
