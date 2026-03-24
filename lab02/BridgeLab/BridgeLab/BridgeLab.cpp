#include <windows.h>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <shlobj.h>

using namespace std;

// ==================== BRIDGE PATTERN ====================

class Formatter {
public:
    virtual ~Formatter() = default;
    virtual string formatTitle(const string& title) const = 0;
    virtual string formatAuthor(const string& author) const = 0;
    virtual string formatContent(const string& content) const = 0;
    virtual string formatFooter() const = 0;
    virtual bool exportFile(const string& filepath, const string& title,
        const string& author, const string& content) const = 0;
    virtual string getFileExtension() const = 0;
    virtual string getFormatName() const = 0;
};

class WordFormat : public Formatter {
public:
    string formatTitle(const string& title) const override {
        return "<html><head><meta charset='UTF-8'><title>" + title + "</title></head><body>\n"
            "<h1 style='font-size:24pt; color:#1F4E79;'>" + title + "</h1>\n";
    }
    string formatAuthor(const string& author) const override {
        return "<p style='font-style:italic; color:#666;'>Author: " + author + "</p>\n<hr>\n";
    }
    string formatContent(const string& content) const override {
        return "<div style='font-family:Times New Roman; font-size:12pt; line-height:1.5;'>" +
            content + "</div>\n";
    }
    string formatFooter() const override {
        return "<hr>\n<p style='color:#999;'>Document created in Word format</p>\n</body></html>";
    }
    bool exportFile(const string& filepath, const string& title,
        const string& author, const string& content) const override {
        ofstream file(filepath, ios::out);
        if (file.is_open()) {
            file << formatTitle(title);
            file << formatAuthor(author);
            file << formatContent(content);
            file << formatFooter();
            file.close();
            return true;
        }
        return false;
    }
    string getFileExtension() const override { return ".doc"; }
    string getFormatName() const override { return "Word"; }
};

class ArticleDocFormat : public Formatter {
public:
    string formatTitle(const string& title) const override {
        return "<!DOCTYPE html>\n<html><head><meta charset='UTF-8'><title>" + title +
            "</title></head><body>\n"
            "<article style='max-width:800px; margin:0 auto; padding:40px; "
            "font-family:Georgia, serif;'>\n"
            "<h1 style='text-align:center; border-bottom:3px solid #333; padding-bottom:10px;'>"
            + title + "</h1>\n";
    }
    string formatAuthor(const string& author) const override {
        return "<p style='text-align:center; font-style:italic;'>Author: " + author +
            "</p>\n<p style='text-align:center;'>UDC: 00.01</p>\n"
            "<div style='background:#f5f5f5; padding:15px; margin:20px 0;'>"
            "<strong>Abstract:</strong>\n";
    }
    string formatContent(const string& content) const override {
        return "</div>\n<section style='line-height:1.8; text-align:justify;'>" +
            content + "</section>\n";
    }
    string formatFooter() const override {
        return "<footer style='margin-top:40px; padding-top:20px; border-top:1px solid #ccc;'>"
            "<p style='text-align:center; color:#666;'>Article Document Format</p>"
            "</footer>\n</article>\n</body></html>";
    }
    bool exportFile(const string& filepath, const string& title,
        const string& author, const string& content) const override {
        ofstream file(filepath, ios::out);
        if (file.is_open()) {
            file << formatTitle(title);
            file << formatAuthor(author);
            file << formatContent(content);
            file << formatFooter();
            file.close();
            return true;
        }
        return false;
    }
    string getFileExtension() const override { return ".article"; }
    string getFormatName() const override { return "ArticleDoc"; }
};

class ResumeFormat : public Formatter {
public:
    string formatTitle(const string& title) const override {
        return "<!DOCTYPE html>\n<html><head><meta charset='UTF-8'><title>Resume</title></head>"
            "<body style='font-family:Arial, sans-serif; background:#f9f9f9;'>\n"
            "<div style='max-width:700px; margin:40px auto; background:white; "
            "padding:40px; box-shadow:0 2px 10px rgba(0,0,0,0.1);'>\n"
            "<h1 style='text-align:center; color:#2C3E50; border-bottom:4px solid #3498DB; "
            "padding-bottom:15px; margin-bottom:30px;'>" + title + "</h1>\n";
    }
    string formatAuthor(const string& author) const override {
        return "<div style='background:#34495E; color:white; padding:20px; margin-bottom:30px; "
            "text-align:center;'>\n"
            "<h2 style='margin:0; font-size:28px;'>" + author + "</h2>\n"
            "<p style='margin:5px 0 0 0; opacity:0.9;'>Professional Resume</p>\n</div>\n";
    }
    string formatContent(const string& content) const override {
        return "<section style='margin-bottom:30px;'>\n"
            "<h3 style='color:#2C3E50; border-left:4px solid #3498DB; "
            "padding-left:15px;'>WORK EXPERIENCE</h3>\n"
            "<div style='line-height:1.8; color:#555;'>" + content + "</div>\n</section>\n";
    }
    string formatFooter() const override {
        return "<footer style='text-align:center; color:#999; font-size:12px; "
            "margin-top:40px; padding-top:20px; border-top:1px solid #eee;'>"
            "Resume Format | Confidential Document\n</footer>\n</div>\n</body></html>";
    }
    bool exportFile(const string& filepath, const string& title,
        const string& author, const string& content) const override {
        ofstream file(filepath, ios::out);
        if (file.is_open()) {
            file << formatTitle(title);
            file << formatAuthor(author);
            file << formatContent(content);
            file << formatFooter();
            file.close();
            return true;
        }
        return false;
    }
    string getFileExtension() const override { return ".resume"; }
    string getFormatName() const override { return "Resume"; }
};

class PdfFormat : public Formatter {
public:
    string formatTitle(const string& title) const override {
        return "%PDF-1.4\n1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /Resources << /Font << /F1 4 0 R >> >> "
            "/Contents 5 0 R >>\nendobj\n"
            "4 0 obj\n<< /Type /Font /Subtype /Type1 /BaseFont /Times-Roman >>\nendobj\n"
            "5 0 obj\n<< /Length 200 >>\nstream\n"
            "BT /F1 24 Tf 50 750 Td (" + title + ") Tj\n"
            "ET\n";
    }
    string formatAuthor(const string& author) const override {
        return "BT /F1 12 Tf 50 720 Td (Author: " + author + ") Tj\nET\n";
    }
    string formatContent(const string& content) const override {
        string formatted = content;
        size_t pos = 0;
        while ((pos = formatted.find('\n', pos)) != string::npos) {
            formatted.replace(pos, 1, ") Tj\nET\nBT /F1 12 Tf 50 ");
            pos += 35;
        }
        return "BT /F1 12 Tf 50 680 Td (" + formatted + ") Tj\nET\n";
    }
    string formatFooter() const override {
        return "endstream\nendobj\nxref\n0 6\n0000000000 65535 f\n"
            "0000000009 00000 n\n0000000058 00000 n\n0000000115 00000 n\n"
            "0000000214 00000 n\n0000000283 00000 n\n"
            "trailer\n<< /Size 6 /Root 1 0 R >>\nstartxref\n550\n%%EOF\n";
    }
    bool exportFile(const string& filepath, const string& title,
        const string& author, const string& content) const override {
        ofstream file(filepath, ios::out);
        if (file.is_open()) {
            file << formatTitle(title);
            file << formatAuthor(author);
            file << formatContent(content);
            file << formatFooter();
            file.close();
            return true;
        }
        return false;
    }
    string getFileExtension() const override { return ".pdf"; }
    string getFormatName() const override { return "PDF"; }
};

class Text {
protected:
    string title, author, content;
    unique_ptr<Formatter> formatter;
public:
    Text(string t, string a, string c, unique_ptr<Formatter> f)
        : title(move(t)), author(move(a)), content(move(c)), formatter(move(f)) {
    }
    virtual ~Text() = default;


    bool exportTo(const string& filepath) const {
        string builtContent = buildContent();
        return formatter->exportFile(filepath, title, author, builtContent);
    }

    virtual string buildContent() const = 0;
    virtual string getCategory() const = 0;
    string getFormatterName() const { return formatter->getFormatName(); }
    string getFileExtension() const { return formatter->getFileExtension(); }
};

class Essay : public Text {
public:
    Essay(string t, string a, string c, unique_ptr<Formatter> f)
        : Text(move(t), move(a), move(c), move(f)) {
    }
    string buildContent() const override {
        return "<h2>Introduction</h2>\n" + content + "\n<h2>Conclusion</h2>\n";
    }
    string getCategory() const override { return "Essay"; }
};

class ScientificText : public Text {
public:
    ScientificText(string t, string a, string c, unique_ptr<Formatter> f)
        : Text(move(t), move(a), move(c), move(f)) {
    }
    string buildContent() const override {
        return "<h2>Abstract</h2>\n" + content + "\n<h2>References</h2>\n";
    }
    string getCategory() const override { return "ScientificText"; }
};

class BusinessLetter : public Text {
public:
    BusinessLetter(string t, string a, string c, unique_ptr<Formatter> f)
        : Text(move(t), move(a), move(c), move(f)) {
    }
    string buildContent() const override {
        return "<p>Dear Sir/Madam,</p>\n" + content + "\n<p>Sincerely,<br>" + author + "</p>\n";
    }
    string getCategory() const override { return "BusinessLetter"; }
};

class CreativeStory : public Text {
public:
    CreativeStory(string t, string a, string c, unique_ptr<Formatter> f)
        : Text(move(t), move(a), move(c), move(f)) {
    }
    string buildContent() const override {
        return "<p style='font-style:italic;'>Once upon a time...</p>\n" + content +
            "\n<p style='font-style:italic;'>The End.</p>\n";
    }
    string getCategory() const override { return "CreativeStory"; }
};

// ==================== GUI ====================
HWND hTitleEdit, hAuthorEdit, hContentEdit;
HWND hEssayRadio, hScientificRadio, hBusinessRadio, hCreativeRadio;
HWND hWordRadio, hArticleRadio, hResumeRadio, hPdfRadio;
HWND hSetUpButton, hResultLabel;
HINSTANCE hInst;

int selectedCategory = 0;
int selectedFormat = 0;

void UpdateRadioButtons() {
    SendMessage(hEssayRadio, BM_SETCHECK, (selectedCategory == 1) ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(hScientificRadio, BM_SETCHECK, (selectedCategory == 2) ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(hBusinessRadio, BM_SETCHECK, (selectedCategory == 3) ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(hCreativeRadio, BM_SETCHECK, (selectedCategory == 4) ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(hWordRadio, BM_SETCHECK, (selectedFormat == 1) ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(hArticleRadio, BM_SETCHECK, (selectedFormat == 2) ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(hResumeRadio, BM_SETCHECK, (selectedFormat == 3) ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(hPdfRadio, BM_SETCHECK, (selectedFormat == 4) ? BST_CHECKED : BST_UNCHECKED, 0);
}

// Получение пути к рабочему столу
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

    unique_ptr<Formatter> selectedFormatPtr;
    switch (selectedFormat) {
    case 1: selectedFormatPtr = make_unique<WordFormat>(); break;
    case 2: selectedFormatPtr = make_unique<ArticleDocFormat>(); break;
    case 3: selectedFormatPtr = make_unique<ResumeFormat>(); break;
    case 4: selectedFormatPtr = make_unique<PdfFormat>(); break;
    }

    unique_ptr<Text> document;
    switch (selectedCategory) {
    case 1: document = make_unique<Essay>(title, author, content, move(selectedFormatPtr)); break;
    case 2: document = make_unique<ScientificText>(title, author, content, move(selectedFormatPtr)); break;
    case 3: document = make_unique<BusinessLetter>(title, author, content, move(selectedFormatPtr)); break;
    case 4: document = make_unique<CreativeStory>(title, author, content, move(selectedFormatPtr)); break;
    }

    // Путь к папке на рабочем столе
    string desktopPath = GetDesktopPath();
    string targetPath = desktopPath + "\\ооап 2 семестр\\лаба2";

    // Создаём имя файла
    string filename = "export_" + document->getCategory() + "_" +
        document->getFormatterName() + document->getFileExtension();
    string fullpath = targetPath + "\\" + filename;

    // Пробуем сохранить
    if (document->exportTo(fullpath)) {
        string msg = "✓ Файл успешно создан:\n\n" + fullpath;
        SetWindowTextA(hResultLabel, msg.c_str());
        MessageBoxA(hWnd, msg.c_str(), "Успех!", MB_OK | MB_ICONINFORMATION);
    }
    else {
        string errorMsg = "✗ Не удалось создать файл!\n\nПуть: " + fullpath +
            "\n\nПроверьте, существует ли папка:\n" + targetPath;
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
        hEssayRadio = CreateWindowA("BUTTON", "Essay", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            10, 240, 100, 20, hWnd, (HMENU)101, hInst, NULL);
        hScientificRadio = CreateWindowA("BUTTON", "Scientific", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            10, 260, 100, 20, hWnd, (HMENU)102, hInst, NULL);
        hBusinessRadio = CreateWindowA("BUTTON", "Business", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            10, 280, 100, 20, hWnd, (HMENU)103, hInst, NULL);
        hCreativeRadio = CreateWindowA("BUTTON", "Creative", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            10, 300, 100, 20, hWnd, (HMENU)104, hInst, NULL);

        CreateWindowA("STATIC", "Format:", WS_VISIBLE | WS_CHILD, 150, 215, 70, 20, hWnd, NULL, hInst, NULL);
        hWordRadio = CreateWindowA("BUTTON", "Word", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            150, 240, 100, 20, hWnd, (HMENU)201, hInst, NULL);
        hArticleRadio = CreateWindowA("BUTTON", "Article", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            150, 260, 100, 20, hWnd, (HMENU)202, hInst, NULL);
        hResumeRadio = CreateWindowA("BUTTON", "Resume", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            150, 280, 100, 20, hWnd, (HMENU)203, hInst, NULL);
        hPdfRadio = CreateWindowA("BUTTON", "PDF", WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            150, 300, 100, 20, hWnd, (HMENU)204, hInst, NULL);

        hSetUpButton = CreateWindowA("BUTTON", "SetUp", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 335, 150, 35, hWnd, (HMENU)1, hInst, NULL);
        hResultLabel = CreateWindowA("STATIC", "", WS_VISIBLE | WS_CHILD | SS_CENTER,
            10, 380, 360, 30, hWnd, NULL, hInst, NULL);
        break;
    }
    case WM_COMMAND: {
        int id = LOWORD(wParam);
        if (id >= 101 && id <= 104) {
            selectedCategory = id - 100;
            UpdateRadioButtons();
            break;
        }
        if (id >= 201 && id <= 204) {
            selectedFormat = id - 200;
            UpdateRadioButtons();
            break;
        }
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
    HWND hWnd = CreateWindowExA(0, "TextEditor", "Text Editor - Bridge Pattern",
        WS_OVERLAPPEDWINDOW, 100, 100, 420, 500, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}