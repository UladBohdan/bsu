class CMyDialog : public CDialog
{
public:
	int val;
	CMyDialog():CDialog(MAKEINTRESOURCE(IDD_DIALOG1)){};
	BOOL OnInitDialog();
	void OnOK();
};