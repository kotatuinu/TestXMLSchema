// TestXMLSchema.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <Windows.h>



int main(int argc, TCHAR* argv[])
{
	int iRtn = -1;

	CoInitialize(NULL);

	if (argc != 4) {
		fprintf(stderr, "INVALID ARGUENTS.\n");
		goto FUNC_END;
	}

	try {
		MSXML2::IXMLDOMDocument2Ptr pXMLDoc;
		MSXML2::IXMLDOMSchemaCollection2Ptr pSchemaCache;
		MSXML2::IXMLDOMParseErrorPtr pErr;

		HRESULT hr;
		hr = pXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
		if (FAILED(hr)) {
			fprintf(stderr, "CREATE INSTANCE FAILED.(MSXML2::DOMDocument60)\n");
			goto FUNC_END;
		}
		hr = pSchemaCache.CreateInstance(__uuidof(MSXML2::XMLSchemaCache60));
		if (FAILED(hr)) {
			fprintf(stderr, "CREATE INSTANCE FAILED.(MSXML2::XMLSchemaCache60)\n");
			goto FUNC_END;
		}
		hr = pSchemaCache->add(_bstr_t(argv[3]), _variant_t(argv[2]));

		pXMLDoc->schemas = pSchemaCache.GetInterfacePtr();
		pXMLDoc->async = VARIANT_FALSE;
		pXMLDoc->validateOnParse = VARIANT_TRUE;
		pXMLDoc->resolveExternals = VARIANT_TRUE;

		VARIANT_BOOL vRslt = pXMLDoc->load(_variant_t(argv[1]));
		if (vRslt != VARIANT_TRUE) {
			pErr = pXMLDoc->parseError;
			printf("resone:%s\nsource:%s\nline:%d\n",
				(TCHAR*)pErr->Getreason(),
				(TCHAR*)pErr->GetsrcText(),
				pErr->Getline());
		}

		iRtn = 1;
	}
	catch(_com_error &e)
	{
		printf("desc:%s\nErrMsg:%s\nErrNo:0x%08x\nsource:%s\n",
			(char*)_bstr_t(e.Description()),
			e.ErrorMessage(),
			e.Error(),
			(char*)e.Source());
		
	}
	catch (...) {

	}


FUNC_END:
	CoUninitialize();
	return iRtn;
}

