// WindowsProject3.cpp : Uygulamanın giriş noktasını tanımlar.
//

#include "framework.h"

#include "WindowsProject3.h"

#include "Environment.h"

#include <time.h>

#include <d2d1_1.h>

#define MAX_LOADSTRING 100
Graphics * graphics;
// Genel Değişkenler:
HINSTANCE hInst;
// geçerli örnek 
#define chms 'text';
#define Max_Size 10;

WCHAR szTitle[MAX_LOADSTRING]; // Başlık çubuğu metni
WCHAR szWindowClass[MAX_LOADSTRING]; // ana pencere sınıfı adı

// Bu kod modülündeki işlevlerin bildirimlerini ilet:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPWSTR lpCmdLine,
  _In_ int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  Environment::Init();
  // TODO: Kodu buraya yerleştirin.

  // Genel dizeleri başlat
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_WINDOWSPROJECT3, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // Uygulama başlatması gerçekleştir:

  if (!InitInstance(hInstance, nCmdShow)) {
    return FALSE;
  }

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT3));

  MSG msg;

  // Ana ileti döngüsü:
  while (GetMessage( & msg, nullptr, 0, 0)) {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, & msg)) {
      TranslateMessage( & msg);
      DispatchMessage( & msg);
    }
  }

  return (int) msg.wParam;
}

//
//  İŞLEV: MyRegisterClass()
//
//  AMAÇ: Pencere sınıfını kaydeder.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT3));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT3);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW( & wcex);
}

//
//   İŞLEV: InitInstance(HINSTANCE, int)
//
//   AMAÇ: Örnek tanıtıcısını kaydeder ve ana pencereyi oluşturur
//
//   AÇIKLAMALAR:
//
//        Bu işlevde, örnek tanıtıcısını genel değişkene kaydederiz ve
//        ana program penceresini oluşturur ve görüntüleriz.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  hInst = hInstance; // Örnek tanıtıcısını genel değişkenimizde depola

  HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

  if (!hWnd) {
    return FALSE;
  }

  int a = 100;
  * & a = 200;
  DomParser * parser = new DomParser();
  String _str;
  _str += "ameno morasi binaero";
  graphics = new Graphics;
  graphics -> Init(hWnd);
  std::string mystr;
  mystr = _str.c_str();
  std::string str = "<html> <a deneme='dfdfdfdffdfdfd'></a>  </html>";
  time_t start;
  time_t end;

  time( & start);
  for (int i = 0; i < 496; i++) {
    _str += 'a';
  }
  time( & end);
  time_t second = end - start;

  time( & start);
  for (int i = 0; i < 496; i++) {
    mystr += 'a';
  }

  time( & end);
  time_t newsecond = end - start;
  if (newsecond > second) {

  }
  const char * chr = _str.c_str();

  parser -> Parse(str);
  Uri uri("https://www.youtube.com/watch?v=f0HiX_n0Fng");
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

//
//  İŞLEV: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  AMAÇ: Ana pencere için iletileri işler.
//
//  WM_COMMAND  - uygulama menüsünü işle
//  WM_PAINT    - Ana pencereyi boya
//  WM_DESTROY  - bir çıkış iletisi gönder ve dön
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_COMMAND: {
    int wmId = LOWORD(wParam);
    // Menü seçimlerini ayrıştır:
    switch (wmId) {
    case IDM_ABOUT:
      DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
      break;
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
  }
  break;
  case WM_PAINT: {
    graphics -> BeginDraw();

    // TODO: Buraya hdc kullanan herhangi bir çizim kodu ekleyin...
    // EndPaint(hWnd, &ps);
    graphics -> EndDraw();

  }
  break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

// Hakkında kutusu için ileti işleyicisi.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
  UNREFERENCED_PARAMETER(lParam);
  switch (message) {
  case WM_INITDIALOG:
    return (INT_PTR) TRUE;

  case WM_COMMAND:
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
      EndDialog(hDlg, LOWORD(wParam));
      return (INT_PTR) TRUE;
    }
    break;
  }
  return (INT_PTR) FALSE;
}
