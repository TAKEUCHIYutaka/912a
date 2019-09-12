// W912a.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "W912a.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

const int Nu = 3120; const int Nr = 4208;
int numu, numr,i,num;
double t1[3][Nu][Nr];
unsigned int tem[3][Nu][Nr * 2];
unsigned int c1[Nu][Nr];


// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_W912A, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_W912A));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_W912A));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_W912A);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		DragAcceptFiles(hWnd,TRUE);
		
		break;

	case WM_DROPFILES:
		HDROP hdrop;
		WCHAR filename[MAX_PATH];
		
		

		hdrop = (HDROP)wParam;
		/* ドロップされたファイルの個数を得る */
		//num = DragQueryFile(hdrop, -1, NULL, 0);
		/* ファイルを処理 */
		for (i = 0; i < 2; i++) {
			DragQueryFile(hdrop, i, filename, sizeof(filename));
			/*
			 * filename にファイル名が入っているので、ここで処理を行う。
			 */
		
			
				fstream file;
				char buf[1];
				unsigned char bufa[1];

				file.open(filename, ios::in | ios::binary);

				while (!file.eof()) {
					file.read(buf, sizeof(buf));
					int k = 0;
					bufa[k] = buf[k];

					for (int k = 0, size = file.gcount(); k < size; ++k) {

						tem[i][numu][numr] = bufa[k];
						++numr;
						if (numr == (Nr + Nr)) {
							numr = 0;
							++numu;
						}
					}
				}
				file.close();
			

			for (numu = 0; numu < Nu; ++numu) {
				for (numr = 0; numr < Nr; ++numr) {
					t1[i][numu][numr] = (tem[i][numu][numr * 2] + tem[i][numu][(numr * 2) + 1] * 256) / 4;

				}
			}


		}
		
		DragFinish(hdrop);


		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
			case ID_32771://連続
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[numu][numr] =( t1[0][numu][numr] + t1[1][numu][numr])/2;
					}
				}
				break;
			case ID_32772://色
				break;
			case ID_32773://スケール
				break;
			case ID_32774://保存
			{
				
					fstream file;
					ofstream ofs("0912AA22.ppm");

					ofs << "P3\n#4208x3120\n4208 3120\n255\n";
					
						if (ofs) {
							for (numu = 0; numu <3120; ++numu)
							{
								for (numr = 0; numr < Nr; numr++)
								{
									ofs << c1[numu][numr] << ' '; ofs << c1[numu][numr] << ' '; ofs << c1[numu][numr] << ' ';
									if (numr == 4207)
									{
										ofs << "\n";
									}

								}
							}
						
					}
					file.close();
				
			}
				break;
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...
            EndPaint(hWnd, &ps);
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

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
