#pragma once
#include "scene.hpp"

#include <filesystem>
#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <SFML\Graphics.hpp>

namespace fs = std::filesystem;
using BlockPos = sf::Vector2<uint16_t>;

struct Block {
  std::wstring name;
  sf::Vector2u txPos;
  uint16_t breakTime;
};

struct BlockRenderInfo {
  std::size_t id;
  sf::Vertex vt[4];
};

class SceneMinecraft : public Scene {
  Context *context_ = nullptr;
  sf::VertexBuffer vbo;
  sf::Vertex vtMouseBar[48];
  sf::Texture tileset;
  bool work_ = true;

  std::vector<std::vector<BlockRenderInfo>> renderInfo;
  std::vector<Block> block;

  BlockPos size;
  uint32_t blockTotal;
  uint8_t verticalOffset;
public:

  SceneMinecraft() {
    size.x = sf::VideoMode::getDesktopMode().width / 64;
    size.y = sf::VideoMode::getDesktopMode().height / 64;
    blockTotal = size.x * size.y;

    verticalOffset = sf::VideoMode::getDesktopMode().height % 64;

    vbo.setPrimitiveType(sf::Quads);
    vbo.setUsage(sf::VertexBuffer::Stream);
    vbo.create(blockTotal * 4 + 48);

    renderInfo.resize(size.x);

    for(uint16_t i = 0; i < size.x; i++) {
      renderInfo[i].resize(size.y);
      for(uint16_t j = 0; j < size.y; j++) {
        BlockRenderInfo &block = renderInfo[i][j];
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
    blockLoader();
  }

  virtual int play(Screen *screen) override {
    screen_ = screen;
    while(work_) {
      screen_->ignoreEvents();
      update();
      draw();
    }
    return NULL;
  }

  virtual void update() override {
    const sf::Vector2i mousePos = sf::Mouse::getPosition();
    vtMouseBar[0].position = sf::Vector2f(mousePos) + sf::Vector2f(16, -48);
    vtMouseBar[1].position = sf::Vector2f(mousePos) + sf::Vector2f(16, -16);
    vtMouseBar[2].position = sf::Vector2f(mousePos) + sf::Vector2f(48, -16);
    vtMouseBar[3].position = sf::Vector2f(mousePos) + sf::Vector2f(48, -48);
    vbo.update(vtMouseBar, 4, blockTotal * 4);
  }

  virtual void draw() override {
    screen_->window.clear(sf::Color::Transparent);
    //screen_->window.draw(vbo, &tileset);
    screen_->window.display();
  }

private:
  void updateBlock(BlockPos pos) {
    vbo.update(renderInfo[pos.x][pos.y].vt, 4, (pos.x + pos.y * size.x) * 4);
  }

  void blockLoader() {
    FILE *file;
    char buff[1024];
    fs::path path;
    for(const auto &entry : fs::directory_iterator("assets\\blocks\\")) {
      if(!fs::is_regular_file(entry)) {
        std::wcout << L"Not a file" << std::endl;
        continue;
      }
      path = entry.path();
      if(path.extension().wstring() != L".json") {
        std::wcout << L"Not a JSON" << std::endl;
        continue;
      }

      std::wcout << L"File: " << path.wstring() << std::endl;

      _wfopen_s(&file, path.wstring().c_str(), L"r");
      if(!file) {
        std::wcout << L"Error opening" << std::endl;
        continue;
      }

      rapidjson::FileReadStream fileStream(file, buff, sizeof(buff));
      rapidjson::EncodedInputStream<rapidjson::UTF16LE<>, rapidjson::FileReadStream> encodedInputStream(fileStream);
      rapidjson::GenericDocument<rapidjson::UTF16LE<>> json;
      json.ParseStream(encodedInputStream);
      fclose(file);

      block.emplace_back();
      Block &bl = block.back();
      if(!json.IsObject()) {
        std::wcout << L"Not an object" << std::endl;
        continue;
      }
      if(!json.HasMember(L"name")) {
        std::wcout << L"No member \"name\"" << std::endl;
        continue;
      }
      if(!json[L"name"].IsString()) {
        std::wcout << L"Member \"name\" not string" << std::endl;
      }
      bl.name = json[L"name"].GetString();

      if(!json.HasMember(L"texture")) {
        std::wcout << L"No member \"texture\"" << std::endl;
        continue;
      }
      if(!json[L"texture"].IsArray()) {
        std::wcout << L"Member \"texture\" not array" << std::endl;
        continue;
      }
      if(json[L"texture"].Size() < 2) {
        std::wcout << L"Member \"texture\" has size smaller than 2" << std::endl;
        continue;
      }
      if(!json[L"texture"][0].IsInt()) {
        std::wcout << L"Member \"texture\" has not integer content" << std::endl;
        continue;
      }
      if(!json[L"texture"][1].IsInt()) {
        std::wcout << L"Member \"texture\" has not integer content" << std::endl;
        continue;
      }
      bl.txPos.x = json[L"name"][0].GetInt();
      bl.txPos.y = json[L"name"][1].GetInt();
      std::wcout << L"Loaded" << std::endl;
    }
  }
};