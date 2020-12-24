
// Face_RecognitionDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Face_Recognition.h"
#include "Face_RecognitionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFaceRecognitionDlg 对话框



CFaceRecognitionDlg::CFaceRecognitionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FACE_RECOGNITION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFaceRecognitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_regResult);
}

BEGIN_MESSAGE_MAP(CFaceRecognitionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENVIDEO, &CFaceRecognitionDlg::OnBnClickedOpenvideo)
	ON_BN_CLICKED(IDC_CLOSEVIDEO, &CFaceRecognitionDlg::OnBnClickedClosevideo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_TAKE_PICTURE, &CFaceRecognitionDlg::OnBnClickedTakePicture)
	ON_BN_CLICKED(IDC_FACE_DETECT, &CFaceRecognitionDlg::OnBnClickedFaceDetect)
	ON_BN_CLICKED(IDC_FEATURE_POINT, &CFaceRecognitionDlg::OnBnClickedFeaturePoint)
	ON_BN_CLICKED(IDC_FACE_ALIGNMENT, &CFaceRecognitionDlg::OnBnClickedFaceAlignment)
	ON_BN_CLICKED(IDC_OFFLINE_FACECMP, &CFaceRecognitionDlg::OnBnClickedOfflineFacecmp)
	ON_BN_CLICKED(IDC_TARGET_TRACKING, &CFaceRecognitionDlg::OnBnClickedTargetTracking)
	ON_BN_CLICKED(IDC_EYE, &CFaceRecognitionDlg::OnBnClickedEye)
	ON_BN_CLICKED(IDC_MOUTH, &CFaceRecognitionDlg::OnBnClickedMouth)
END_MESSAGE_MAP()


// CFaceRecognitionDlg 消息处理程序

BOOL CFaceRecognitionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	cv::namedWindow("OPENCV", cv::WINDOW_AUTOSIZE);//设置窗口名
	HWND hWnd = (HWND)cvGetWindowHandle("OPENCV");//hWnd 表示窗口句柄,获取窗口句柄
	HWND hParent = ::GetParent(hWnd); //取窗口的父窗口句柄
	::SetParent(hWnd, GetDlgItem(IDC_VIDEO)->m_hWnd); // 设置新的父窗口句柄
	::ShowWindow(hParent, SW_HIDE); //隐葳原openCV窗口的边框

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFaceRecognitionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFaceRecognitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFaceRecognitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 按键1：打开摄像头
void CFaceRecognitionDlg::OnBnClickedOpenvideo()
{
	// TODO: 在此添加控件通知处理程序代码
	m_flag = 1;
	m_bdetect = 0;
	m_brectangle = 0;
	m_btrack = 0;

	CRect rect1;

	//定义一个CWnd对象，获取IDC_PIC0控件的ID
	CWnd* pWnd = GetDlgItem(IDC_VIDEO);

	//把大小，赋值给 CRect的类
	//GetClientRect为获得控件相自身的坐标大小
	pWnd->GetClientRect(&rect1);
	//GetDlgItem(IDC_IMAGE)->GetClientRect(&rect1);

	int x = rect1.Width();
	int y = rect1.Height();

	//防止摄像头连续打开两次
	m_capture.release();

	m_capture = VideoCapture(0);

	//防止摄像头打不开
	if (!m_capture.isOpened())
	{
		fprintf(stderr, "Can not open camera.\n");
		return;
	}

	frontal_face_detector detector = get_frontal_face_detector();
	shape_predictor pose_model;

	// F:\Face_Detection\MyProject\model_data
	deserialize("F:\\Face_Detection\\MyProject\\model_data\\shape_predictor_68_face_landmarks.dat") >> pose_model;
	//image_window win, win_faces;

	bool bFirst = 1;
	while (m_flag)
	{
		cv::Mat frame;
		m_capture >> frame;
		cv::resize(frame, m_dst, cv::Size(x, y), 0, 0, 1);
		cv::Mat image_fliped;
		cv::flip(frame, image_fliped, 1); //因为摄像头镜像
		frame = image_fliped;

		dlib::cv_image<bgr_pixel> cimg(frame); //cv::Mat 转 dlib::cv_image

		// 目标跟踪
		if (m_btrack)
		{
			//全局变量才不会被释放掉
			//image_window m_win;

			if (bFirst)
			{
				m_tracker.start_track(cimg, centered_rect(point(200, 110), 86, 86));
				m_win.set_image(cimg);
				m_win.add_overlay(m_tracker.get_position());
				bFirst = 0;
			}
			m_tracker.update(cimg);
			m_win.set_image(cimg);
			m_win.clear_overlay();
			m_win.add_overlay(m_tracker.get_position());
		}


		// 5.人脸检测（画出人脸矩形框）
		if (m_bdetect)
		{
			std::vector<dlib::rectangle> faces = detector(cimg);
			std::vector<full_object_detection> shapes;

			for (unsigned long i = 0; i < faces.size(); ++i)
			{
				if (m_brectangle)
				{
					cv::rectangle(frame, Rect(faces[i].left(), faces[i].top(), faces[i].width(), faces[i].height()), Scalar(0, 255, 0), 1, 1);

				}
				shapes.push_back(pose_model(cimg, faces[i]));
			}

			if (!shapes.empty())
			{
				// 6.绘制特征点
				for (int i = 0; i < 68; i++)
				{
					//cv::rectangle(frame, Rect(100, 300, 20, 200), Scalar(255, 0, 0), 1, 1, 0);
					if (!m_brectangle)
					{
						cv::circle(frame, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 3, cv::Scalar(0, 255, 0), -1);
						//	shapes[0].part(i).x();//68个
						// zhanzl:显示特征点的数字： “0 - 67” 
						putText(frame, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 0, 0), 1, 4);
					}
				}


				//眨眼检测
				if (m_beye)
				{
					//眨眼行为检测:左眼-上下四个点
					int y37 = shapes[0].part(37).y();
					int y38 = shapes[0].part(38).y();
					int y40 = shapes[0].part(40).y();
					int y41 = shapes[0].part(41).y();
					int x36 = shapes[0].part(36).x();
					int x39 = shapes[0].part(39).x();

					//1 / 2 * [(y41 + y40) - (y37 + y38)] / (x39 - x36)
					//float flg = 1/2* [(y41 + y40) - (y37 + y48)]/(x39 - x36);
					int y1 = abs(y37 - y41);
					int y2 = abs(y38 - y40);
					int x1 = abs(x39 - x36);
					//长宽比
					float flg = (y1 + y2) / (2.0 * x1);

					CString str;
					str.Format(_T("EYE EAR：%.2f"), flg);
					m_regResult.SetWindowText(str);
				}

				//张嘴检测：Abs(Y50 – Y58) + Abs(Y52-56) /(2.0 * ABS(x48-x54))
				if (m_bmouth)
				{
					int y50 = shapes[0].part(50).y();
					int y52 = shapes[0].part(52).y();
					int y56 = shapes[0].part(56).y();
					int y58 = shapes[0].part(58).y();

					int x48 = shapes[0].part(48).x();
					int x54 = shapes[0].part(54).x();

					int y1 = abs(y50 - y58);
					int y2 = abs(y52 - y56);
					int x1 = abs(x48 - x54);

					//长宽比
					float flg = (y1 + y2) / (2.0 * x1);

					CString str;
					str.Format(_T("Mouth EAR：%.2f"), flg);
					m_regResult.SetWindowText(str);
				}

				//复制一份出来
				std::vector<matrix<rgb_pixel>> vect_faces;

				//04-人脸对齐：face_chips为对齐后的目标
				dlib::array<matrix<rgb_pixel> > face_chips;
				dlib::extract_image_chips(cimg, get_face_chip_details(shapes), face_chips);
				for (size_t i = 0; i < face_chips.size(); i++)
				{
					//复制一份人脸特征出来
					vect_faces.push_back(move(face_chips[i]));

					cv::Mat img = dlib::toMat(face_chips[i]);
					string picpath;
					stringstream stream;
					stream << i;
					picpath = stream.str();
					picpath += ".jpg";
					imwrite(picpath, img);
					//显示在控件上
					ShowImage2(picpath, 0, 0);
				}



			}
		}

		cv::imshow("OPENCV", frame);
		cv::waitKey(30);
	}
}


// 按键2：关闭摄像头
void CFaceRecognitionDlg::OnBnClickedClosevideo()
{
	// TODO: 在此添加控件通知处理程序代码
	m_flag = 0;
}


void CFaceRecognitionDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_flag = 0;

	CDialogEx::OnClose();
}

// 函数：显示图片
BOOL CFaceRecognitionDlg::ShowImage(CDC* pDC, string strPath, int x, int y)
{
	IPicture* pPic = NULL;
	OleLoadPicturePath(CComBSTR(strPath.c_str()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);
	if (NULL == pPic)
	{
		return FALSE;
	}
	// 宽度+高度
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//宽度和高度  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		pPic->Release();
		return false;
	}
	//释放资源
	pPic->Release();
	return true;
}


// 按键3：抓拍人脸
void CFaceRecognitionDlg::OnBnClickedTakePicture()
{
	// TODO: 在此添加控件通知处理程序代码
	//抓拍出来的图片的保存地址
	string picpath = "F://Face_Detection//MyProject//Face_Recognition//001.jpg";
	imwrite(picpath, m_dst);
	Mat image = imread(picpath);
	Mat imagedst;
	CWnd* pWnd = GetDlgItem(IDC_PICTURE);
	CDC* pDC = NULL;
	CString strPath;
	((CStatic*)GetDlgItem(IDC_PICTURE))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	pDC = GetDlgItem(IDC_PICTURE) -> GetDC();
	ShowImage(pDC, picpath, 0, 0);
	ReleaseDC(pDC);
}


// 按键4：人脸检测
void CFaceRecognitionDlg::OnBnClickedFaceDetect()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bdetect = 1;
	if (m_brectangle)
	{
		m_brectangle = 0;
	}
	else
	{
		m_brectangle = 1;
	}
}


// 按键5:特征点标定
void CFaceRecognitionDlg::OnBnClickedFeaturePoint()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bdetect)
	{
		m_bdetect = 0;
	}
	else
	{
		m_bdetect = 1;
	}
}

//显示图片
BOOL CFaceRecognitionDlg::ShowImage2(string strPath, int x, int y)
{
	//
	//strPath = "d:\\001.jpg";
	CWnd* pWnd = GetDlgItem(IDC_VIDEO);
	//showMatImgToWnd(pWnd,image);
	CDC* pDC = NULL;
	//设置静态控件的样式，使其可以使用位图，并使位图显示居中  
	((CStatic*)GetDlgItem(IDC_VIDEO))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);

	pDC = GetDlgItem(IDC_VIDEO)->GetDC();
	ShowImage(pDC, strPath, 0, 0);


	//
	IPicture* pPic = NULL;
	OleLoadPicturePath(CComBSTR(strPath.c_str()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);
	if (NULL == pPic)
	{
		return FALSE;
	}
	// 宽度+高度
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//宽度和高度  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		pPic->Release();
		return false;
	}
	//释放资源
	pPic->Release();

	ReleaseDC(pDC); //释放资源
	return true;
}

//函数：显示图片-左侧
BOOL CFaceRecognitionDlg::ShowImageLeft(string strPath, int x, int y)
{

	//strPath = "F://Face_Detection//MyProject//My_FACESIGNIN//001.jpg";
	CWnd* pWnd = GetDlgItem(IDC_VIDEO);
	//showMatImgToWnd(pWnd,image);
	CDC* pDC = NULL;
	//设置静态控件的样式，使其可以使用位图，并使位图显示居中  
	((CStatic*)GetDlgItem(IDC_VIDEO))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);

	pDC = GetDlgItem(IDC_VIDEO)->GetDC();
	ShowImage(pDC, strPath, 0, 0);


	//
	IPicture* pPic = NULL;
	OleLoadPicturePath(CComBSTR(strPath.c_str()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);
	if (NULL == pPic)
	{
		return FALSE;
	}
	// 宽度+高度
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//宽度和高度  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		pPic->Release();
		return false;
	}
	//释放资源
	pPic->Release();

	ReleaseDC(pDC); //释放资源
	return true;
}


// 函数：显示图片-右侧
BOOL CFaceRecognitionDlg::ShowImageRight(string strPath, int x, int y)
{
	//
	//strPath = "F://Face_Detection//MyProject//My_FACESIGNIN//001.jpg";
	CWnd* pWnd = GetDlgItem(IDC_PICTURE);
	//showMatImgToWnd(pWnd,image);
	CDC* pDC = NULL;
	//设置静态控件的样式，使其可以使用位图，并使位图显示居中  
	((CStatic*)GetDlgItem(IDC_PICTURE))->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);

	pDC = GetDlgItem(IDC_PICTURE)->GetDC();
	ShowImage(pDC, strPath, 0, 0);


	//
	IPicture* pPic = NULL;
	OleLoadPicturePath(CComBSTR(strPath.c_str()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture, (LPVOID*)&pPic);
	if (NULL == pPic)
	{
		return FALSE;
	}
	// 宽度+高度
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;
	pPic->get_Width(&hmWidth);
	pPic->get_Height(&hmHeight);
	//宽度和高度  
	RECT rtWnd;
	pDC->GetWindow()->GetWindowRect(&rtWnd);
	int iWndWidth = rtWnd.right - rtWnd.left;
	int iWndHeight = rtWnd.bottom - rtWnd.top;

	if (FAILED(pPic->Render(*pDC, x, y, iWndWidth, iWndHeight, 0, hmHeight, hmWidth, -hmHeight, NULL)))
	{
		pPic->Release();
		return false;
	}
	//释放资源
	pPic->Release();

	ReleaseDC(pDC); //释放资源
	return true;
}

// 按键6：人脸对齐
void CFaceRecognitionDlg::OnBnClickedFaceAlignment()
{
	// TODO: 在此添加控件通知处理程序代码
	string filePath = "F://Face_Detection//MyProject//Face_Recognition//001.jpg";
	ShowImageLeft(filePath, 0, 0);
	dlib::array2d<dlib::bgr_pixel> img; //使用dlib载入彩色的RGB图像
	dlib::load_image(img, filePath);
	dlib::pyramid_up(img);

	frontal_face_detector detector = get_frontal_face_detector();
	shape_predictor pose_model;
	deserialize("F:\\Face_Detection\\MyProject\\model_data\\shape_predictor_68_face_landmarks.dat") >> pose_model;

	std::vector<dlib::rectangle> faces = detector(img);

	std::vector<full_object_detection> shapes;
	for (unsigned long i = 0; i < faces.size(); ++i) {
		//人脸检测，并绘制矩形框 
		// Key1:注意转换失真问题：bgr_pixel
		cv::Mat img2 = dlib::toMat(img); //dlib::array2d 转 Mat
		cv::rectangle(img2, Rect(faces[i].left(), faces[i].top(), faces[i].width(), faces[i].height()), Scalar(0, 0, 255), 1, 1, 0);
		shapes.push_back(pose_model(img, faces[i]));
	}

	if (!shapes.empty()) {

		for (int i = 0; i < 68; i++) {
			cv::Mat img2 = dlib::toMat(img);
			cv::circle(img2, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 3, cv::Scalar(0, 0, 255), -1);
			putText(img2, to_string(i), cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 0, 0), 1, 4);
		}
	}

	// 6.人脸对齐：face_chips为对齐后的目标
	dlib::array<array2d<bgr_pixel> > face_chips;
	dlib::extract_image_chips(img, get_face_chip_details(shapes), face_chips);
	for (size_t i = 0; i < face_chips.size(); i++)
	{
		cv::Mat img = dlib::toMat(face_chips[i]);
		string picpath;
		stringstream stream;
		stream << i;
		picpath = stream.str();
		picpath += ".jpg";
		picpath = "F://Face_Detection//MyProject//Face_Recognition//" + picpath;
		imwrite(picpath, img);
		//显示在控件上
		ShowImageRight(picpath, 0, 0);
	}
}



// 按键8：人脸离线比对
void CFaceRecognitionDlg::OnBnClickedOfflineFacecmp()
{
	// TODO: 在此添加控件通知处理程序代码
	frontal_face_detector detector = get_frontal_face_detector();
	shape_predictor sp;

	deserialize("F:\\Face_Detection\\MyProject\\model_data\\shape_predictor_68_face_landmarks.dat") >> sp;

	//导入模型：人脸识别
	anet_type net;

	//dlib_face_recognition_resnet_model_v1
	deserialize("F:\\Face_Detection\\MyProject\\model_data\\dlib_face_recognition_resnet_model_v1.dat") >> net;

	string path1 = "F:\\Face_Detection\\MyProject\\Face_Recognition\\faces\\001.jpg";
	string path2 = "F:\\Face_Detection\\MyProject\\Face_Recognition\\faces\\002.jpg";

	matrix<rgb_pixel> img1;
	load_image(img1, path1);

	matrix<rgb_pixel> img2;
	load_image(img2, path2);

	ShowImageLeft(path1, 0, 0);
	ShowImageRight(path2, 0, 0);

	std::vector<matrix<rgb_pixel>> face1;
	std::vector<matrix<rgb_pixel>> face2;

	for (auto face : detector(img1))
	{
		auto shape = sp(img1, face);
		matrix<rgb_pixel> face_chip;
		extract_image_chip(img1, get_face_chip_details(shape, 150, 0.25), face_chip);
		face1.push_back(move(face_chip));
	}

	if (face1.size() == 0)
	{
		cout << "No faces founded in the image1." << endl;
	}

	for (auto face : detector(img2))
	{
		//001-特征点检测
		auto shape = sp(img2, face);
		//0002-特征点对齐
		matrix<rgb_pixel> face_chip;
		extract_image_chip(img2, get_face_chip_details(shape, 150, 0.25), face_chip);
		//003-特征点存储（对齐后的点）
		face2.push_back(move(face_chip));
	}

	if (face2.size() == 0)
	{
		cout << "No faces founded in the image2." << endl;
	}

	std::vector<matrix<float, 0, 1>> face_descriptors1 = net(face1);
	std::vector<matrix<float, 0, 1>> face_descriptors2 = net(face2);

	//计算 欧式距离
	float f = length(face_descriptors1[0] - face_descriptors2[0]);
	// 一般阈值设置为 0.6 或者 0.7
	
	CString str;
	if (f > 0 && f < 0.5) {
		str.Format(_T("欧氏距离: %.2f，是同一个人"), f);
	}
	else {
		str.Format(_T("欧氏距离: %.2f，不是同一个人"), f);
	}
	m_regResult.SetWindowText(str);
	AfxMessageBox(str); //此处是弹窗文字
}


// 按键9:目标跟踪
void CFaceRecognitionDlg::OnBnClickedTargetTracking()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_btrack)
	{
		m_btrack = 0;
	}
	else
	{
		m_btrack = 1;
	}

}

// 按键10：眨眼识别
void CFaceRecognitionDlg::OnBnClickedEye()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_beye)
	{
		m_beye = 0;
	}
	else
	{
		m_beye = 1;
	}
}

// 按键11：张嘴识别
void CFaceRecognitionDlg::OnBnClickedMouth()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bmouth)
	{
		m_bmouth = 0;
	}
	else
	{
		m_bmouth = 1;
	}
}
