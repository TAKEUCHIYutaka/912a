﻿// W912a.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "W912a.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING]; // メイン ウィンドウ クラス名
HWND hWnd, hDlg1, hDlg2, hDlg3,hDlg4;


#define MAX_WIDTH       (4120)
#define MAX_HEIGHT      (3120)

LPCWSTR texting;
const int Nu = 3120; const int Nr = 4208;
int numu = 0; int numr = 0; int i=0 ; int num=0;
double t1[3][Nu][Nr];
unsigned int tem[3][Nu][Nr * 2];
unsigned int c1[2][Nu][Nr];


// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Pict1Proc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Pict2Proc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Pict3Proc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Pict4Proc(HWND, UINT, WPARAM, LPARAM);

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
      512, 256, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
		DragAcceptFiles(hWnd, TRUE);
		texting = TEXT("あと2ファイル取得できます。");
		break;
	
	case WM_DROPFILES:
		
		HDROP hdrop;
		WCHAR filename[MAX_PATH];
		

		hdrop = (HDROP)wParam;

		texting = TEXT("読み込んでいます");
		UpdateWindow(hWnd);

		/* ドロップされたファイルの個数を得る */
		//num = DragQueryFile(hdrop, -1, NULL, 0);
		/* ファイルを処理 */
		//for (i = 0; i < 2; i++) {
			DragQueryFile(hdrop, num, filename, sizeof(filename));
			/*
			  filename にファイル名が入っているので、ここで処理を行う。*/
			
			

			{
				

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
			}

			for (numu = 0; numu < Nu; ++numu) {
				for (numr = 0; numr < Nr; ++numr) {
					t1[i][numu][numr] = (tem[i][numu][numr * 2] + tem[i][numu][(numr * 2) + 1] * 256) / 4;

				}
			}


		

		DragFinish(hdrop);
		numu = 0; numr = 0;
		i++;
		if (i == 1) {
			texting = TEXT("あと1ファイル取得できます。");
		}
		else if (i == 2) {
			texting = TEXT("ファイル取得が完了しました。");
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
			switch (wmId)
			{
			case ID_32775://グレーノンスケール
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[0][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr] + t1[1][numu][numr]) / 3;
					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_32787://グレースケール
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[0][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr] + t1[1][numu][numr]) / 3;
					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_32788://yellowのンスケール
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[0][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr]) / 3;
						c1[1][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr] + t1[1][numu][numr]) / 3;
					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_32789://yellowスケール
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[0][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr]) / 3;
						c1[1][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr] + t1[1][numu][numr]) / 3;
					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BLUE_32808://blueNONスケール
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[0][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr]) / 3;
						c1[1][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr] + t1[1][numu][numr]) / 3;
					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_BLUE_32810://blueスケール
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[0][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr]) / 3;
						c1[1][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr] + t1[1][numu][numr]) / 3;
					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_RED_32812://redNONスケール
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[0][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr]) / 3;
						c1[1][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr] + t1[1][numu][numr]) / 3;
					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_RED_32814://redNONスケール
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[0][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr]) / 3;
						c1[1][numu][numr] = (t1[0][numu][numr] + t1[0][numu][numr] + t1[1][numu][numr]) / 3;
					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_32780://単独1nonスケール
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[0][numu][numr] = t1[0][numu][numr];

					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case ID_32781://単独2ﾉﾝｽｹｰﾙ
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[1][numu][numr] = t1[1][numu][numr];

					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_32785://単独1スケール
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[0][numu][numr] = t1[0][numu][numr];

					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case ID_32786://単独2スケール
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[0][numu][numr] = t1[0][numu][numr];

					}
				}
				texting = TEXT("画像データが作成されました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case ID_32790://グレーのンスケール保存

				static OPENFILENAME     ofn;
				static TCHAR        szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = hWnd;
					ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
					ofn.lpstrFile = szFile;       // 選択ファイル格納
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = TEXT(".ppm");
					ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
					ofn.lpstrTitle = TEXT("画像を保存します。");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);

				}

				texting = TEXT("保存中です。。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
				
				{
				fstream file;
				ofstream ofs(szFile);

				ofs << "P3\n#4208x3120\n4208 3120\n255\n";

				if (ofs) {
					for (numu = 0; numu < 3120; ++numu)
					{

						for (numr = 0; numr < Nr; ++numr)
						{
							ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' ';
							if (numr == 4207)
							{
								ofs << "\n";



							}
						}
					}

				}
				file.close();
			}
					texting = TEXT("保存が完了しました。");
					InvalidateRect(hWnd, NULL, TRUE);
			
				break;


			case ID_32798://グレースケール保存
			{
				static OPENFILENAME     ofn;
				static TCHAR        szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = hWnd;
					ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
					ofn.lpstrFile = szFile;       // 選択ファイル格納
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = TEXT(".ppm");
					ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
					ofn.lpstrTitle = TEXT("画像を保存します。");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);
				}

				texting = TEXT("保存中です。。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);

				fstream file;
				ofstream ofs(szFile);

				ofs << "P3\n#4208x3120\n4208 3120\n255\n";

				if (ofs) {
					for (numu = 0; numu < Nu; ++numu)
					{
						for (numr = 0; numr < Nr; ++numr)
						{
							if (numu > 3100 && numu < 3106 && numr>3930 && numr < 4056) {
								ofs <<0 << ' '; ofs << 0 << ' '; ofs << 0 << ' ';
							}
							else if (numu > 3105 && numu < 3111 && numr>3930 && numr < 4056) {
								ofs << 255 << ' '; ofs << 255 << ' '; ofs << 255 << ' ';
							}
							else {
								ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' ';
								if (numr == 4207)
								{
									ofs << "\n";

								}
							}
						}
					}

				}
				file.close();

			}
			texting = TEXT("保存が完了しました。");
			InvalidateRect(hWnd, NULL, TRUE);
			break;

			case ID_32792://yellowのンスケール保存
			{
			
				{
				static OPENFILENAME     ofn;
				static TCHAR        szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = hWnd;
					ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
					ofn.lpstrFile = szFile;       // 選択ファイル格納
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = TEXT(".ppm");
					ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
					ofn.lpstrTitle = TEXT("画像を保存します。");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);

				}

				texting = TEXT("保存中です。。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
				
					fstream file;
					ofstream ofs(szFile);

					ofs << "P3\n#4208x3120\n4208 3120\n255\n";

					if (ofs) {
						for (numu = 0; numu < 3120; ++numu)
						{

							for (numr = 0; numr < Nr; ++numr)
							{
								ofs << c1[1][numu][numr] << ' '; ofs << c1[1][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' ';
								if (numr == 4207)
								{
									ofs << "\n";



								}
							}
						}

					}
					file.close();
				}
				texting = TEXT("保存が完了しました。");
				InvalidateRect(hWnd, NULL, TRUE);

			

			}
			break;

			case ID_32793://yellowスケール
			{
				static OPENFILENAME     ofn;
				static TCHAR        szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = hWnd;
					ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
					ofn.lpstrFile = szFile;       // 選択ファイル格納
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = TEXT(".ppm");
					ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
					ofn.lpstrTitle = TEXT("画像を保存します。");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);
				}

				texting = TEXT("保存中です。。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
				
				fstream file;
				ofstream ofs(szFile);

				ofs << "P3\n#4208x3120\n4208 3120\n255\n";

				if (ofs) {
					for (numu = 0; numu < Nu; ++numu)
					{
						for (numr = 0; numr < Nr; ++numr)
						{
							if (numu > 3100 && numu < 3106 && numr>3930 && numr < 4056) {
								ofs << 0 << ' '; ofs << 0 << ' '; ofs << 0 << ' ';
							}
							else if (numu > 3105 && numu < 3111 && numr>3930 && numr < 4056) {
								ofs << 255 << ' '; ofs << 255 << ' '; ofs << 255 << ' ';
							}
							else {
								ofs << c1[1][numu][numr] << ' '; ofs << c1[1][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' ';
								if (numr == 4207)
								{
									ofs << "\n";

								}
							}
						}
					}

				}
				file.close();
				texting = TEXT("保存が完了しました。");
				InvalidateRect(hWnd, NULL, TRUE);

			}
				break;
				
				/**/

			case ID_BLUE_32809://blueのンスケール保存
			{
			
				{
					static OPENFILENAME     ofn;
					static TCHAR        szPath[MAX_PATH];
					static TCHAR            szFile[MAX_PATH];

					if (szPath[0] == TEXT('\0')) {
						GetCurrentDirectory(MAX_PATH, szPath);
					}
					if (ofn.lStructSize == 0) {
						ofn.lStructSize = sizeof(OPENFILENAME);
						ofn.hwndOwner = hWnd;
						ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
						ofn.lpstrFile = szFile;       // 選択ファイル格納
						ofn.nMaxFile = MAX_PATH;
						ofn.lpstrDefExt = TEXT(".ppm");
						ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
						ofn.lpstrTitle = TEXT("画像を保存します。");
						ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
					}
					if (GetSaveFileName(&ofn)) {
						MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);

					}

					texting = TEXT("保存中です。。");
					InvalidateRect(hWnd, NULL, TRUE);
					UpdateWindow(hWnd);

					fstream file;
					ofstream ofs(szFile);

					ofs << "P3\n#4208x3120\n4208 3120\n255\n";

					if (ofs) {
						for (numu = 0; numu < 3120; ++numu)
						{

							for (numr = 0; numr < Nr; ++numr)
							{
								ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' '; ofs << c1[1][numu][numr] << ' ';
								if (numr == 4207)
								{
									ofs << "\n";



								}
							}
						}

					}
					file.close();
				}
				texting = TEXT("保存が完了しました。");
				InvalidateRect(hWnd, NULL, TRUE);



			}
			break;

			case ID_BLUE_32811://blueスケール
			{
				static OPENFILENAME     ofn;
				static TCHAR        szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = hWnd;
					ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
					ofn.lpstrFile = szFile;       // 選択ファイル格納
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = TEXT(".ppm");
					ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
					ofn.lpstrTitle = TEXT("画像を保存します。");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);
				}

				texting = TEXT("保存中です。。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);

				fstream file;
				ofstream ofs(szFile);

				ofs << "P3\n#4208x3120\n4208 3120\n255\n";

				if (ofs) {
					for (numu = 0; numu < Nu; ++numu)
					{
						for (numr = 0; numr < Nr; ++numr)
						{
							if (numu > 3100 && numu < 3106 && numr>3930 && numr < 4056) {
								ofs << 0 << ' '; ofs << 0 << ' '; ofs << 0 << ' ';
							}
							else if (numu > 3105 && numu < 3111 && numr>3930 && numr < 4056) {
								ofs << 255 << ' '; ofs << 255 << ' '; ofs << 255 << ' ';
							}
							else {
								ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' '; ofs << c1[1][numu][numr] << ' ';
								if (numr == 4207)
								{
									ofs << "\n";

								}
							}
						}
					}

				}
				file.close();
				texting = TEXT("保存が完了しました。");
				InvalidateRect(hWnd, NULL, TRUE);

			}
			break;

			case ID_RED_32813://redのンスケール保存
			{
			
				{
					static OPENFILENAME     ofn;
					static TCHAR        szPath[MAX_PATH];
					static TCHAR            szFile[MAX_PATH];

					if (szPath[0] == TEXT('\0')) {
						GetCurrentDirectory(MAX_PATH, szPath);
					}
					if (ofn.lStructSize == 0) {
						ofn.lStructSize = sizeof(OPENFILENAME);
						ofn.hwndOwner = hWnd;
						ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
						ofn.lpstrFile = szFile;       // 選択ファイル格納
						ofn.nMaxFile = MAX_PATH;
						ofn.lpstrDefExt = TEXT(".ppm");
						ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
						ofn.lpstrTitle = TEXT("画像を保存します。");
						ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
					}
					if (GetSaveFileName(&ofn)) {
						MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);

					}

					texting = TEXT("保存中です。。");
					InvalidateRect(hWnd, NULL, TRUE);
					UpdateWindow(hWnd);

					fstream file;
					ofstream ofs(szFile);

					ofs << "P3\n#4208x3120\n4208 3120\n255\n";

					if (ofs) {
						for (numu = 0; numu < 3120; ++numu)
						{

							for (numr = 0; numr < Nr; ++numr)
							{
								ofs << c1[1][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' ';
								if (numr == 4207)
								{
									ofs << "\n";



								}
							}
						}

					}
					file.close();
				}
				texting = TEXT("保存が完了しました。");
				InvalidateRect(hWnd, NULL, TRUE);



			}
			break;

			case ID_RED_32815://redスケール
			{
				static OPENFILENAME     ofn;
				static TCHAR        szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = hWnd;
					ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
					ofn.lpstrFile = szFile;       // 選択ファイル格納
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = TEXT(".ppm");
					ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
					ofn.lpstrTitle = TEXT("画像を保存します。");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);
				}

				texting = TEXT("保存中です。。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);

				fstream file;
				ofstream ofs(szFile);

				ofs << "P3\n#4208x3120\n4208 3120\n255\n";

				if (ofs) {
					for (numu = 0; numu < Nu; ++numu)
					{
						for (numr = 0; numr < Nr; ++numr)
						{
							if (numu > 3100 && numu < 3106 && numr>3930 && numr < 4056) {
								ofs << 0 << ' '; ofs << 0 << ' '; ofs << 0 << ' ';
							}
							else if (numu > 3105 && numu < 3111 && numr>3930 && numr < 4056) {
								ofs << 255 << ' '; ofs << 255 << ' '; ofs << 255 << ' ';
							}
							else {
								ofs << c1[1][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' ';
								if (numr == 4207)
								{
									ofs << "\n";

								}
							}
						}
					}

				}
				file.close();
				texting = TEXT("保存が完了しました。");
				InvalidateRect(hWnd, NULL, TRUE);

			}
			break;

			case ID_32794://単1のンスケール保存
			{
			
				{
					static OPENFILENAME     ofn;
					static TCHAR        szPath[MAX_PATH];
					static TCHAR            szFile[MAX_PATH];

					if (szPath[0] == TEXT('\0')) {
						GetCurrentDirectory(MAX_PATH, szPath);
					}
					if (ofn.lStructSize == 0) {
						ofn.lStructSize = sizeof(OPENFILENAME);
						ofn.hwndOwner = hWnd;
						ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
						ofn.lpstrFile = szFile;       // 選択ファイル格納
						ofn.nMaxFile = MAX_PATH;
						ofn.lpstrDefExt = TEXT(".ppm");
						ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
						ofn.lpstrTitle = TEXT("画像を保存します。");
						ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
					}
					if (GetSaveFileName(&ofn)) {
						MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);

					}

					texting = TEXT("保存中です。。");
					InvalidateRect(hWnd, NULL, TRUE);
					UpdateWindow(hWnd);

					fstream file;
					ofstream ofs(szFile);

					ofs << "P3\n#4208x3120\n4208 3120\n255\n";

					if (ofs) {
						for (numu = 0; numu < 3120; ++numu)
						{

							for (numr = 0; numr < Nr; ++numr)
							{
								ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' ';
								if (numr == 4207)
								{
									ofs << "\n";



								}
							}
						}

					}
					file.close();
				}
				texting = TEXT("保存が完了しました。");
				InvalidateRect(hWnd, NULL, TRUE);



			}
			break;

			case ID_32796://単1スケール
			{
				static OPENFILENAME     ofn;
				static TCHAR        szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = hWnd;
					ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
					ofn.lpstrFile = szFile;       // 選択ファイル格納
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = TEXT(".ppm");
					ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
					ofn.lpstrTitle = TEXT("画像を保存します。");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);
				}

				texting = TEXT("保存中です。。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);

				fstream file;
				ofstream ofs(szFile);

				ofs << "P3\n#4208x3120\n4208 3120\n255\n";

				if (ofs) {
					for (numu = 0; numu < Nu; ++numu)
					{
						for (numr = 0; numr < Nr; ++numr)
						{
							if (numu > 3100 && numu < 3106 && numr>3930 && numr < 4056) {
								ofs << 0 << ' '; ofs << 0 << ' '; ofs << 0 << ' ';
							}
							else if (numu > 3105 && numu < 3111 && numr>3930 && numr < 4056) {
								ofs << 255 << ' '; ofs << 255 << ' '; ofs << 255 << ' ';
							}
							else {
								ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' '; ofs << c1[0][numu][numr] << ' ';
								if (numr == 4207)
								{
									ofs << "\n";

								}
							}
						}
					}

				}
				file.close();
				texting = TEXT("保存が完了しました。");
				InvalidateRect(hWnd, NULL, TRUE);

			}
			break;
			
			/**/
			case ID_32795://単2のンスケール保存
			{
				

				{
					static OPENFILENAME     ofn;
					static TCHAR        szPath[MAX_PATH];
					static TCHAR            szFile[MAX_PATH];

					if (szPath[0] == TEXT('\0')) {
						GetCurrentDirectory(MAX_PATH, szPath);
					}
					if (ofn.lStructSize == 0) {
						ofn.lStructSize = sizeof(OPENFILENAME);
						ofn.hwndOwner = hWnd;
						ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
						ofn.lpstrFile = szFile;       // 選択ファイル格納
						ofn.nMaxFile = MAX_PATH;
						ofn.lpstrDefExt = TEXT(".ppm");
						ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
						ofn.lpstrTitle = TEXT("画像を保存します。");
						ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
					}
					if (GetSaveFileName(&ofn)) {
						MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);

					}

					texting = TEXT("保存中です。。");
					InvalidateRect(hWnd, NULL, TRUE);
					UpdateWindow(hWnd);

					fstream file;
					ofstream ofs(szFile);

					ofs << "P3\n#4208x3120\n4208 3120\n255\n";

					if (ofs) {
						for (numu = 0; numu < 3120; ++numu)
						{

							for (numr = 0; numr < Nr; ++numr)
							{
								ofs << c1[1][numu][numr] << ' '; ofs << c1[1][numu][numr] << ' '; ofs << c1[1][numu][numr] << ' ';
								if (numr == 4207)
								{
									ofs << "\n";



								}
							}
						}

					}
					file.close();
				}
				texting = TEXT("保存が完了しました。");
				InvalidateRect(hWnd, NULL, TRUE);



			}
			break;

			case ID_32797://単2スケール
			{
				static OPENFILENAME     ofn;
				static TCHAR        szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = hWnd;
					ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
					ofn.lpstrFile = szFile;       // 選択ファイル格納
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = TEXT(".ppm");
					ofn.lpstrFilter = TEXT("ppmファイル(*.ppm)\0*.ppm\0");
					ofn.lpstrTitle = TEXT("画像を保存します。");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);
				}

				texting = TEXT("保存中です。。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);

				fstream file;
				ofstream ofs(szFile);

				ofs << "P3\n#4208x3120\n4208 3120\n255\n";

				if (ofs) {
					for (numu = 0; numu < Nu; ++numu)
					{
						for (numr = 0; numr < Nr; ++numr)
						{
							if (numu > 3100 && numu < 3106 && numr>3930 && numr < 4056) {
								ofs << 0 << ' '; ofs << 0 << ' '; ofs << 0 << ' ';
							}
							else if (numu > 3105 && numu < 3111 && numr>3930 && numr < 4056) {
								ofs << 255 << ' '; ofs << 255 << ' '; ofs << 255 << ' ';
							}
							else {
								ofs << c1[1][numu][numr] << ' '; ofs << c1[1][numu][numr] << ' '; ofs << c1[1][numu][numr] << ' ';
								if (numr == 4207)
								{
									ofs << "\n";

								}
							}
						}
					}

				}
				file.close();
				texting = TEXT("保存が完了しました。");
				InvalidateRect(hWnd, NULL, TRUE);

			}
			break;

			case ID_YELLOW_32816:
				texting = TEXT("表示の準備中です。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
				hDlg1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_FORMVIEW), hWnd, (DLGPROC)Pict1Proc);
				ShowWindow(hDlg1, SW_SHOW);
				break;
			case ID_BLUE_32817:
				texting = TEXT("表示の準備中です。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
				hDlg2 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_FORMVIEW), hWnd, (DLGPROC)Pict2Proc);
				ShowWindow(hDlg2, SW_SHOW);
				break;
			case ID_RED_32818:
				texting = TEXT("表示の準備中です。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
				hDlg3 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_FORMVIEW), hWnd, (DLGPROC)Pict3Proc);
				ShowWindow(hDlg3, SW_SHOW);
				break;
			case ID_32819:
				texting = TEXT("表示の準備中です。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
				hDlg3 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_FORMVIEW), hWnd, (DLGPROC)Pict4Proc);
				ShowWindow(hDlg4, SW_SHOW);
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
	
			TextOut(hdc, 10, 10,texting,wcslen(texting));
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



LRESULT CALLBACK Pict1Proc(HWND hDlg1, UINT message, WPARAM wParam, LPARAM lParam)//Y
{
	static HBITMAP  hBitmap;    // ビットマップ
	static HDC      hMemDC;     // オフスクリーン
	static UINT     saveX;
	static UINT     saveY;
	static SCROLLINFO scrInfoH, scrInfoV;

	switch (message)
	{

	case WM_CLOSE:
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
		DestroyWindow(hDlg1);
		break;

	case WM_INITDIALOG:
		HDC hDC;

		// DCコンパチブルの作成
		hDC = GetDC(hDlg1);
		hMemDC = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, MAX_WIDTH, MAX_HEIGHT);
		SelectObject(hMemDC, hBitmap);
		ReleaseDC(hDlg1, hDC);

		for (numu = 0; numu < Nu; ++numu) {
			for (numr = 0; numr < Nr; ++numr) {
				SetPixel(hMemDC, numr, numu, RGB(c1[1][numu][numr], c1[1][numu][numr], c1[0][numu][numr]));
			}
		}
		  

		//横スクロールバー初期設定
		scrInfoH.cbSize = sizeof(SCROLLINFO);
		scrInfoH.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoH.nMin = 0;
		scrInfoH.nMax = Nr;
		scrInfoH.nPage = 1;
		scrInfoH.nPos = 0;
		

		//縦スクロールバー初期設定
		scrInfoV.cbSize = sizeof(SCROLLINFO);
		scrInfoV.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoV.nMin = 0;
		scrInfoV.nMax = Nu;
		scrInfoV.nPage = 1;
		scrInfoV.nPos = 0;
		
		texting = TEXT("表示しました。");
		InvalidateRect(hWnd, NULL, TRUE);
		

		break;
	case WM_PAINT:
		PAINTSTRUCT     ps;


		// DCコンパチブルの描画
		hDC = BeginPaint(hDlg1, &ps);
		BitBlt(hDC, 0, 0, MAX_WIDTH, MAX_HEIGHT, hMemDC, scrInfoH.nPos, scrInfoV.nPos, SRCCOPY);
		EndPaint(hDlg1, &ps);

		break;
	case WM_SIZE:
		scrInfoV.nPos = 0;
		scrInfoH.nPos = 0;
		InvalidateRect(hDlg1, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			scrInfoH.nPos += 10;
			InvalidateRect(hDlg1, NULL, TRUE);

			break;
		case VK_LEFT:
			scrInfoH.nPos -= 10;
			InvalidateRect(hDlg1, NULL, TRUE);

			break;
		case VK_UP:
			scrInfoV.nPos -= 10;
			InvalidateRect(hDlg1, NULL, TRUE);

			break;
		case VK_DOWN:
			scrInfoV.nPos += 10;
			InvalidateRect(hDlg1, NULL, TRUE);

			break;
		default:
			break;
		}

	default:
		return DefWindowProc(hDlg1, message, wParam, lParam);
	}
	return 0;
}


LRESULT CALLBACK Pict2Proc(HWND hDlg2, UINT message, WPARAM wParam, LPARAM lParam)//B
{
	static HBITMAP  hBitmap;    // ビットマップ
	static HDC      hMemDC;     // オフスクリーン
	static UINT     saveX;
	static UINT     saveY;
	static SCROLLINFO scrInfoH, scrInfoV;

	switch (message)
	{

	case WM_CLOSE:
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
		DestroyWindow(hDlg2);
		break;

	case WM_INITDIALOG:
		HDC hDC;

		// DCコンパチブルの作成
		hDC = GetDC(hDlg2);
		hMemDC = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, MAX_WIDTH, MAX_HEIGHT);
		SelectObject(hMemDC, hBitmap);
		ReleaseDC(hDlg2, hDC);

		for (numu = 0; numu < Nu; ++numu) {
			for (numr = 0; numr < Nr; ++numr) {
				SetPixel(hMemDC, numr, numu, RGB(c1[0][numu][numr], c1[0][numu][numr], c1[1][numu][numr]));
			}
		}


		//横スクロールバー初期設定
		scrInfoH.cbSize = sizeof(SCROLLINFO);
		scrInfoH.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoH.nMin = 0;
		scrInfoH.nMax = Nr;
		scrInfoH.nPage = 1;
		scrInfoH.nPos = 0;
		

		//縦スクロールバー初期設定
		scrInfoV.cbSize = sizeof(SCROLLINFO);
		scrInfoV.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoV.nMin = 0;
		scrInfoV.nMax = Nu;
		scrInfoV.nPage = 1;
		scrInfoV.nPos = 0;
		
		texting = TEXT("表示しました。");
		InvalidateRect(hWnd, NULL, TRUE);

		break;
	case WM_PAINT:
		PAINTSTRUCT     ps;


		// DCコンパチブルの描画
		hDC = BeginPaint(hDlg2, &ps);
		BitBlt(hDC, 0, 0, MAX_WIDTH, MAX_HEIGHT, hMemDC, scrInfoH.nPos, scrInfoV.nPos, SRCCOPY);
		EndPaint(hDlg2, &ps);

		break;
	case WM_SIZE:
		scrInfoV.nPos = 0;
		scrInfoH.nPos = 0;
		InvalidateRect(hDlg2, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			scrInfoH.nPos += 10;
			InvalidateRect(hDlg2, NULL, TRUE);

			break;
		case VK_LEFT:
			scrInfoH.nPos -= 10;
			InvalidateRect(hDlg2, NULL, TRUE);

			break;
		case VK_UP:
			scrInfoV.nPos -= 10;
			InvalidateRect(hDlg2, NULL, TRUE);

			break;
		case VK_DOWN:
			scrInfoV.nPos += 10;
			InvalidateRect(hDlg2, NULL, TRUE);

			break;
		default:
			break;
		}

	default:
		return DefWindowProc(hDlg2, message, wParam, lParam);
	}
	return 0;
}


LRESULT CALLBACK Pict3Proc(HWND hDlg3, UINT message, WPARAM wParam, LPARAM lParam)//R
{
	static HBITMAP  hBitmap;    // ビットマップ
	static HDC      hMemDC;     // オフスクリーン
	static UINT     saveX;
	static UINT     saveY;
	static SCROLLINFO scrInfoH, scrInfoV;

	switch (message)
	{

	case WM_CLOSE:
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
		DestroyWindow(hDlg3);
		break;

	case WM_INITDIALOG:
		HDC hDC;

		// DCコンパチブルの作成
		hDC = GetDC(hDlg3);
		hMemDC = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, MAX_WIDTH, MAX_HEIGHT);
		SelectObject(hMemDC, hBitmap);
		ReleaseDC(hDlg3, hDC);

		for (numu = 0; numu < Nu; ++numu) {
			for (numr = 0; numr < Nr; ++numr) {
				SetPixel(hMemDC, numr, numu, RGB(c1[1][numu][numr], c1[0][numu][numr], c1[0][numu][numr]));
			}
		}


		//横スクロールバー初期設定
		scrInfoH.cbSize = sizeof(SCROLLINFO);
		scrInfoH.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoH.nMin = 0;
		scrInfoH.nMax = Nr;
		scrInfoH.nPage = 1;
		scrInfoH.nPos = 0;
		

		//縦スクロールバー初期設定
		scrInfoV.cbSize = sizeof(SCROLLINFO);
		scrInfoV.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoV.nMin = 0;
		scrInfoV.nMax = Nu;
		scrInfoV.nPage = 1;
		scrInfoV.nPos = 0;
		
		texting = TEXT("表示しました。");
		InvalidateRect(hWnd, NULL, TRUE);

		break;
	case WM_PAINT:
		PAINTSTRUCT     ps;


		// DCコンパチブルの描画
		hDC = BeginPaint(hDlg3, &ps);
		BitBlt(hDC, 0, 0, MAX_WIDTH, MAX_HEIGHT, hMemDC, scrInfoH.nPos, scrInfoV.nPos, SRCCOPY);
		EndPaint(hDlg3, &ps);

		break;
	case WM_SIZE:
		scrInfoV.nPos = 0;
		scrInfoH.nPos = 0;
		InvalidateRect(hDlg3, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			scrInfoH.nPos += 10;
			InvalidateRect(hDlg3, NULL, TRUE);

			break;
		case VK_LEFT:
			scrInfoH.nPos -= 10;
			InvalidateRect(hDlg3, NULL, TRUE);

			break;
		case VK_UP:
			scrInfoV.nPos -= 10;
			InvalidateRect(hDlg3, NULL, TRUE);

			break;
		case VK_DOWN:
			scrInfoV.nPos += 10;
			InvalidateRect(hDlg3, NULL, TRUE);

			break;
		default:
			break;
		}

	default:
		return DefWindowProc(hDlg3, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK Pict4Proc(HWND hDlg4, UINT message, WPARAM wParam, LPARAM lParam)//グレー
{
	static HBITMAP  hBitmap;    // ビットマップ
	static HDC      hMemDC;     // オフスクリーン
	static UINT     saveX;
	static UINT     saveY;
	static SCROLLINFO scrInfoH, scrInfoV;

	switch (message)
	{

	case WM_CLOSE:
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
		DestroyWindow(hDlg4);
		break;

	case WM_INITDIALOG:
		HDC hDC;

		// DCコンパチブルの作成
		hDC = GetDC(hDlg3);
		hMemDC = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, MAX_WIDTH, MAX_HEIGHT);
		SelectObject(hMemDC, hBitmap);
		ReleaseDC(hDlg4, hDC);

		for (numu = 0; numu < Nu; ++numu) {
			for (numr = 0; numr < Nr; ++numr) {
				SetPixel(hMemDC, numr, numu, RGB(c1[0][numu][numr], c1[0][numu][numr], c1[0][numu][numr]));
			}
		}


		//横スクロールバー初期設定
		scrInfoH.cbSize = sizeof(SCROLLINFO);
		scrInfoH.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoH.nMin = 0;
		scrInfoH.nMax = Nr;
		scrInfoH.nPage = 1;
		scrInfoH.nPos = 0;


		//縦スクロールバー初期設定
		scrInfoV.cbSize = sizeof(SCROLLINFO);
		scrInfoV.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoV.nMin = 0;
		scrInfoV.nMax = Nu;
		scrInfoV.nPage = 1;
		scrInfoV.nPos = 0;

		texting = TEXT("表示しました。");
		InvalidateRect(hWnd, NULL, TRUE);

		break;
	case WM_PAINT:
		PAINTSTRUCT     ps;


		// DCコンパチブルの描画
		hDC = BeginPaint(hDlg4, &ps);
		BitBlt(hDC, 0, 0, MAX_WIDTH, MAX_HEIGHT, hMemDC, scrInfoH.nPos, scrInfoV.nPos, SRCCOPY);
		EndPaint(hDlg4, &ps);

		break;
	case WM_SIZE:
		scrInfoV.nPos = 0;
		scrInfoH.nPos = 0;
		InvalidateRect(hDlg4, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			scrInfoH.nPos += 10;
			InvalidateRect(hDlg4, NULL, TRUE);

			break;
		case VK_LEFT:
			scrInfoH.nPos -= 10;
			InvalidateRect(hDlg4, NULL, TRUE);

			break;
		case VK_UP:
			scrInfoV.nPos -= 10;
			InvalidateRect(hDlg4, NULL, TRUE);

			break;
		case VK_DOWN:
			scrInfoV.nPos += 10;
			InvalidateRect(hDlg4, NULL, TRUE);

			break;
		default:
			break;
		}

	default:
		return DefWindowProc(hDlg4, message, wParam, lParam);
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
