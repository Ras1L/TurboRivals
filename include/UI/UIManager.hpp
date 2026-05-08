#ifndef UI_UI_MANAGER_HPP
#define UI_UI_MANAGER_HPP

class UIManager {
public:
    void Init();
    void Begin(); // Обновляется в основном цикле
    void End();   // между BeginDrawing() и EndDrawing()
    void Deinit();
};

#endif