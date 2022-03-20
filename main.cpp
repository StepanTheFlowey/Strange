#include "main.hpp"

#include "Context.hpp"
#include "SceneJevil.hpp"
#include "SceneMatrix.hpp"

int secureMain() {
  context.load();
  context.create();

  Scene* scene = nullptr;
  switch(rand() % 2) {
    case 0:
      scene = new SceneJevil;
      break;
    case 1:
      scene = new SceneMatrix;
      break;
  }
  scene->run(context);
  delete scene;

  context.save();
  context.destroy();

  return EXIT_SUCCESS;
}

std::wstring wide(const std::string string) {
  return std::wstring(string.begin(), string.end());
}

std::string shrink(const std::wstring wstring) {
  return std::string(wstring.begin(), wstring.end());
}

#ifdef DEBUG
int main() {
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
#endif // DEBUG
  srand(static_cast<unsigned int>(time(0)));
  int exitcode = 0;
  
  try {
    exitcode = secureMain();
  }
  catch(Exeption exeption) {
#ifdef DEBUG
    std::cerr << exeption.wtf().c_str() << std::endl;
#else
    MessageBoxW(NULL, exeption.wtf().c_str(), L"Strange", MB_ICONERROR | MB_OK);
#endif // DEBUG
    exitcode = EXIT_FAILURE;
  }
  catch(...) {
#ifdef DEBUG
    std::cerr << "omg shit happens\a" << std::endl;
#else
    MessageBoxW(NULL, L"omg shit happens", L"Strange", MB_ICONERROR | MB_OK);
#endif // DEBUG
    exitcode = EXIT_FAILURE;
  }

#ifdef DEBUG
  _wsystem(L"pause");
#endif // DEBUG
  exit(exitcode);
}