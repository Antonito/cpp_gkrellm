#ifndef WINDOW_HH_
#define WINDOW_HH_

namespace Graphic
{
  namespace NCurses
  {
    class Window
    {
    public:
      Window();
      ~Window();

      void refresh();

    private:
      Window(Window const &){};
      Window &operator=(Window const &);
    };
  }
}
#endif // !WINDOW_HH_