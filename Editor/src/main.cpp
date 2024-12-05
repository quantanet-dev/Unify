#include <unify.h>

int main()
{
    Unify::UnifyApplication app = Unify::UnifyApplication();

    try
    {
        app.Run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}