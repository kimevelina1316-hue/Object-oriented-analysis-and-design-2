#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <shlobj.h>

using namespace std;

// ==================== БЕЗ ПАТТЕРНА BRIDGE ====================
// Простые классы для каждой комбинации

// Базовый класс для документа
class Document {
protected:
    string title, author, content;
public:
    Document(string t, string a, string c)
        : title(t), author(a), content(c) {
    }
    virtual ~Document() = default;

    virtual bool exportToFile(const string& filepath) const = 0;
    virtual string getCategory() const = 0;
    virtual string getFormat() const = 0;

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getContent() const { return content; }
};

// Эссе в формате Word
class EssayWord : public Document {
public:
    EssayWord(string t, string a, string c) : Document(t, a, c) {}

    string buildContent() const {
        return "<h2>Introduction</h2>\n" + getContent() + "\n<h2>Conclusion</h2>\n";
    }

    bool exportToFile(const string& filepath) const override {
        ofstream file(filepath + ".doc", ios::out);
        if (file.is_open()) {
            file << "<html><head><meta charset='UTF-8'><title>" << getTitle() << "</title></head><body>\n";
            file << "<h1 style='font-size:24pt; color:#1F4E79;'>" << getTitle() << "</h1>\n";
            file << "<p style='font-style:italic; color:#666;'>Author: " << getAuthor() << "</p>\n<hr>\n";
            file << buildContent();
            file << "<hr>\n<p style='color:#999;'>Document created in Word format</p>\n</body></html>";
            file.close();
            return true;
        }
        return false;
    }

    string getCategory() const override { return "Essay"; }
    string getFormat() const override { return "Word"; }
};

// Эссе в формате Article
class EssayArticle : public Document {
public:
    EssayArticle(string t, string a, string c) : Document(t, a, c) {}

    string buildContent() const {
        return "<h2>Introduction</h2>\n" + getContent() + "\n<h2>Conclusion</h2>\n";
    }

    bool exportToFile(const string& filepath) const override {
        ofstream file(filepath + ".article", ios::out);
        if (file.is_open()) {
            file << "<!DOCTYPE html>\n<html><head><meta charset='UTF-8'><title>" << getTitle() << "</title></head><body>\n";
            file << "<article style='max-width:800px; margin:0 auto; padding:40px; font-family:Georgia, serif;'>\n";
            file << "<h1 style='text-align:center; border-bottom:3px solid #333; padding-bottom:10px;'>" << getTitle() << "</h1>\n";
            file << "<p style='text-align:center; font-style:italic;'>Author: " << getAuthor() << "</p>\n";
            file << "<p style='text-align:center;'>UDC: 00.01</p>\n";
            file << "<div style='background:#f5f5f5; padding:15px; margin:20px 0;'><strong>Abstract:</strong>\n";
            file << buildContent();
            file << "</div>\n<footer style='margin-top:40px; padding-top:20px; border-top:1px solid #ccc;'>";
            file << "<p style='text-align:center; color:#666;'>Article Document Format</p></footer>\n</article>\n</body></html>";
            file.close();
            return true;
        }
        return false;
    }

    string getCategory() const override { return "Essay"; }
    string getFormat() const override { return "ArticleDoc"; }
};

// Научный текст в формате Word
class ScientificWord : public Document {
public:
    ScientificWord(string t, string a, string c) : Document(t, a, c) {}

    string buildContent() const {
        return "<h2>Abstract</h2>\n" + getContent() + "\n<h2>References</h2>\n";
    }

    bool exportToFile(const string& filepath) const override {
        ofstream file(filepath + ".doc", ios::out);
        if (file.is_open()) {
            file << "<html><head><meta charset='UTF-8'><title>" << getTitle() << "</title></head><body>\n";
            file << "<h1 style='font-size:24pt; color:#1F4E79;'>" << getTitle() << "</h1>\n";
            file << "<p style='font-style:italic; color:#666;'>Author: " << getAuthor() << "</p>\n<hr>\n";
            file << buildContent();
            file << "<hr>\n<p style='color:#999;'>Document created in Word format</p>\n</body></html>";
            file.close();
            return true;
        }
        return false;
    }

    string getCategory() const override { return "ScientificText"; }
    string getFormat() const override { return "Word"; }
};

// Научный текст в формате Article
class ScientificArticle : public Document {
public:
    ScientificArticle(string t, string a, string c) : Document(t, a, c) {}

    string buildContent() const {
        return "<h2>Abstract</h2>\n" + getContent() + "\n<h2>References</h2>\n";
    }

    bool exportToFile(const string& filepath) const override {
        ofstream file(filepath + ".article", ios::out);
        if (file.is_open()) {
            file << "<!DOCTYPE html>\n<html><head><meta charset='UTF-8'><title>" << getTitle() << "</title></head><body>\n";
            file << "<article style='max-width:800px; margin:0 auto; padding:40px; font-family:Georgia, serif;'>\n";
            file << "<h1 style='text-align:center; border-bottom:3px solid #333; padding-bottom:10px;'>" << getTitle() << "</h1>\n";
            file << "<p style='text-align:center; font-style:italic;'>Author: " << getAuthor() << "</p>\n";
            file << "<p style='text-align:center;'>UDC: 00.01</p>\n";
            file << "<div style='background:#f5f5f5; padding:15px; margin:20px 0;'><strong>Abstract:</strong>\n";
            file << buildContent();
            file << "</div>\n<footer style='margin-top:40px; padding-top:20px; border-top:1px solid #ccc;'>";
            file << "<p style='text-align:center; color:#666;'>Article Document Format</p></footer>\n</article>\n</body></html>";
            file.close();
            return true;
        }
        return false;
    }

    string getCategory() const override { return "ScientificText"; }
    string getFormat() const override { return "ArticleDoc"; }
};

// ==================== GUI ====================
HWND hTitleEdit, hAuthorEdit, hContentEdit;
HWND hEssayRadio, hScientificRadio;
HWND hWordRadio, hArticleRadio;
HWND hSetUpButton, hResultLabel;
HINSTANCE hInst;

int selectedCategory = 0; // 1=Essay, 2=Scientific
int selectedFormat = 0;   // 1=Word, 2=Article

void UpdateRadioButtons() {
    SendMessage(hEssayRadio, BM_SETCHECK, (selectedCategory == 1) ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(hScientificRadio, BM_SETCHECK, (selectedCategory == 2) ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(hWordRadio, BM_SETCHECK, (selectedFormat == 1) ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(hArticleRadio, BM_SETCHECK, (selectedFormat == 2) ? BST_CHECKED : BST_UNCHECKED, 0);
}

string GetDesktopPath() {
    char path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path))) {
        return string(path);
    }
    return "C:\\Users\\Public\\Desktop";
}

void OnSetUpClicked(HWND hWnd) {
    if (selectedCategory == 0 || selectedFormat == 0) {
        MessageBoxA(hWnd, "Выберите категорию и формат!", "Ошибка", MB_OK | MB_ICONWARNING);
        return;
    }

    char title[256], author[256], content[4096];
    GetWindowTextA(hTitleEdit, title, 256);
    GetWindowTextA(hAuthorEdit, author, 256);
    GetWindowTextA(hContentEdit, content, 4096);

    unique_ptr<Document> document;
    string formatName;

    // Создаём нужный документ без паттерна Bridge
    if (selectedCategory == 1 && selectedFormat == 1) {
        document = make_unique<EssayWord>(title, author, content);
        formatName = "Word";
    }
    else if (selectedCategory == 1 && selectedFormat == 2) {
        document = make_unique<EssayArticle>(title, author, content);
        formatName = "ArticleDoc";
    }
    else if (selectedCategory == 2 && selectedFormat == 1) {
        document = make_unique<ScientificWord>(title, author, content);
        formatName = "Word";
    }
    else if (selectedCategory == 2 && selectedFormat == 2) {
        document = make_unique<ScientificArticle>(title, author, content);
        formatName = "ArticleDoc";
    }

    string desktopPath = GetDesktopPath();
    string targetPath = desktopPath + "\\ооап 2 семестр\\лаба2";
    string filename = "export_" + document->getCategory() + "_" + formatName;
    string fullpath = targetPath + "\\" + filename;

    if (document->exportToFile(fullpath)) {
        string msg = "✓ Файл успешно создан:\n\n" + fullpath;
        SetWindowTextA(hResultLabel, msg.c_str());
        MessageBoxA(hWnd, msg.c_str(), "Успех!", MB_OK | MB_ICONINFORMATION);
    }
    else {
        string errorMsg = "✗ Не удалось создать файл!\n\nПуть: " + fullpath;
        MessageBoxA(hWnd, errorMsg.c_str(), "Ошибка", MB_OK | MB_ICONERROR);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        CreateWindowA("STATIC", "Title:", WS_VISIBLE | WS_CHILD, 10, 10, 50, 20, hWnd, NULL, hInst, NULL);
        hTitleEdit = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 70, 10, 300, 25, hWnd, NULL, hInst, NULL);
        CreateWindowA("STATIC", "Author:", WS_VISIBLE | WS_CHILD, 10, 45, 50, 20, hWnd, NULL, hInst, NULL);
        hAuthorEdit = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 70, 45, 300, 25, hWnd, NULL, hInst, NULL);
        CreateWindowA("STATIC", "Content:", WS_VISIBLE | WS_CHILD, 10, 80, 60, 20, hWnd, NULL, hInst, NULL);
        hContentEdit = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE |
            ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL, 70, 80, 300, 120, hWnd, NULL, hInst, NULL);

        CreateWindowA("STATIC", "Category:", WS_VISIBLE | WS_CHILD, 10, 215, 70, 20, hWnd, NULL, hInst, NULL);
        hEssayRadio = CreateWindowA("BUTTON", "Essay", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON | WS_GROUP,
            10, 240, 100, 20, hWnd, (HMENU)101, hInst, NULL);
        hScientificRadio = CreateWindowA("BUTTON", "Scientific", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            10, 260, 100, 20, hWnd, (HMENU)102, hInst, NULL);

        CreateWindowA("STATIC", "Format:", WS_VISIBLE | WS_CHILD, 150, 215, 70, 20, hWnd, NULL, hInst, NULL);
        hWordRadio = CreateWindowA("BUTTON", "Word", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON | WS_GROUP,
            150, 240, 100, 20, hWnd, (HMENU)201, hInst, NULL);
        hArticleRadio = CreateWindowA("BUTTON", "Article", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            150, 260, 100, 20, hWnd, (HMENU)202, hInst, NULL);

        hSetUpButton = CreateWindowA("BUTTON", "SetUp", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 295, 150, 35, hWnd, (HMENU)1, hInst, NULL);
        hResultLabel = CreateWindowA("STATIC", "", WS_VISIBLE | WS_CHILD | SS_CENTER,
            10, 340, 360, 30, hWnd, NULL, hInst, NULL);
        break;
    }
    case WM_COMMAND: {
        int id = LOWORD(wParam);
        if (id == 101) { selectedCategory = 1; UpdateRadioButtons(); break; }
        if (id == 102) { selectedCategory = 2; UpdateRadioButtons(); break; }
        if (id == 201) { selectedFormat = 1; UpdateRadioButtons(); break; }
        if (id == 202) { selectedFormat = 2; UpdateRadioButtons(); break; }
        if (id == 1) OnSetUpClicked(hWnd);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    hInst = hInstance;
    WNDCLASSEXA wc = { sizeof(WNDCLASSEXA), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, NULL, NULL,
                       (HBRUSH)(COLOR_WINDOW + 1), NULL, "TextEditor", NULL };
    RegisterClassExA(&wc);
    HWND hWnd = CreateWindowExA(0, "TextEditor", "Text Editor (NO Bridge Pattern)",
        WS_OVERLAPPEDWINDOW, 100, 100, 420, 450, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}