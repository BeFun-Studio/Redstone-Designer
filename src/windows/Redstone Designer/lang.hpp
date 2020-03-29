#pragma once
#include <Windows.h>
#include <string>
#include "resource.h"
using namespace std;

wstring WelcomeText;
wstring SelectAOptionToContinueText;
wstring ContinueAndCreateANewFileButtonText;
wstring ContinueAndOpenExistingFileButtonText;
wstring ContinueWithoutAnyOperationButtonText;
wstring DescriptionBarNoItemsSelectedText;
wstring DescriptionBarNewFileText;
wstring DescriptionBarOpenExistingFileText;
wstring OutOfMemoryErrorText;
wstring LogicErrorText;
wstring CreateDirectWriteFactoryFailedText;
wstring CreateDirectWriteTextFormatFailedText;
wstring CreateDirect3DDeviceObjectFailed;
wstring CreateDirect3DDeviceContextObjectFailed;
wstring GetDXGIAdapterObjectFailed;
wstring GetDXGIParentObjectFailed;
wstring CreateDirect2DSwapChainObjectFailed;
wstring GetDirect2DBufferObjectFailed;
wstring CreateDirect2DBitmapFromDXGISurfaceObjectFailed;
wstring CreateDirect2DEffectObjectFailed;
wstring CreateDirect2DBrushFailed;
wstring CreateDirect2DGradientStopCollectionFailedText;
wstring DrawWindowContentsFailedText;
wstring PresentWindowContentsFailedText;
wstring CudaSpeedupEnabledText;
wstring CudaSpeedupDisabledText;
wstring OpenCLSpeedupEnabledText;
wstring OpenCLSpeedupDisabledText;
wstring InvalidEvaluationCopyText;
wstring ComErrorText;
wstring OverflowErrorText;
wstring UnderflowErrorText;
wstring ForTestingPurposesOnlyText;
wstring ErrorWindowCaption;
wstring WarningWindowCaption;
wstring InformationWindowCaption;
wstring ConfirmExit;
wstring QueryDirect2DInterfaceFailed;
wstring CreateDirect2DFactoryFailed;
wstring CreateDirect2DDeviceFailed;
wstring CreateDirect2DDeviceContextFailed;
wstring CreateDirect2DRenderTargetFailed;
wstring RegisterWindowClassFailed;
wstring CreateWindowFailed;

enum LANGUAGE_ID
{
	ENGLISH,
	CHINESE_SIMPLIFIED,
	CHINESE_TRADITIONAL
};

LANGUAGE_ID GlobalLanguage;
extern HINSTANCE ApplicationInstance;

class InvalidLanguage
{
};
void LoadLanguageFile(LANGUAGE_ID lang_id)
{
	wchar_t tmpstr[513];
	switch (lang_id)
	{
	case CHINESE_SIMPLIFIED:
		LoadString(ApplicationInstance, IDS_WELCOMETEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		WelcomeText = tmpstr;
		LoadString(ApplicationInstance, IDS_CONTINUE_AND_CREATE_A_NEW_FILE_BUTTON_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		ContinueAndCreateANewFileButtonText = tmpstr;
		LoadString(ApplicationInstance, IDS_CONTINUE_AND_OPEN_EXISTING_FILE_BUTTON_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		ContinueAndOpenExistingFileButtonText = tmpstr;
		LoadString(ApplicationInstance, IDS_SELECT_A_OPTION_TO_CONTINUE_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		SelectAOptionToContinueText = tmpstr;
		LoadString(ApplicationInstance, IDS_CONTINUE_WITHOUT_ANY_OPERATION_BUTTON_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		ContinueWithoutAnyOperationButtonText = tmpstr;
		LoadString(ApplicationInstance, IDS_DESCRIPTION_BAR_NO_ITEMS_SELECTED_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		DescriptionBarNoItemsSelectedText = tmpstr;
		LoadString(ApplicationInstance, IDS_DESCRIPTION_BAR_NEW_FILE_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		DescriptionBarNewFileText = tmpstr;
		LoadString(ApplicationInstance, IDS_DESCRIPTION_BAR_OPEN_EXISTING_FILE_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		DescriptionBarOpenExistingFileText = tmpstr;
		LoadString(ApplicationInstance, IDS_OUT_OF_MEMORY_ERROR_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		OutOfMemoryErrorText = tmpstr;
		LoadString(ApplicationInstance, IDS_LOGIC_ERROR_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		LogicErrorText = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_WRITE_FACTORY_FAILED_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		CreateDirectWriteFactoryFailedText = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_WRITE_TEXT_FORMAT_FAILED_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		CreateDirectWriteTextFormatFailedText = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_3D_DEVICE_OBJECT_FAILED_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		CreateDirect3DDeviceObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_3D_DEVICE_CONTEXT_OBJECT_FAILED_CHINESE_SIMPLIFIED, tmpstr, 512);
		CreateDirect3DDeviceObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_GET_DXGI_ADAPTER_OBJECT_FAILED_CHINESE_SIMPLIFIED, tmpstr, 512);
		CreateDirect3DDeviceContextObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_GET_DXGI_PARENT_OBJECT_FAILED_CHINESE_SIMPLIFIED, tmpstr, 512);
		GetDXGIParentObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_2D_SWAP_CHAIN_OBJECT_FAILED_CHINESE_SIMPLIFIED, tmpstr, 512);
		CreateDirect2DSwapChainObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_GET_DIRECT_2D_SWAP_CHAIN_OBJECT_FAILED_CHINESE_SIMPLIFIED, tmpstr, 512);
		GetDirect2DBufferObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_2D_BITMAP_FROM_DXGI_SURFACE_OBJECT_FAILED_CHINESE_SIMPLIFIED, tmpstr, 512);
		CreateDirect2DBitmapFromDXGISurfaceObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_2D_EFFECT_OBJECT_FAILED_CHINESE_SIMPLIFIED, tmpstr, 512);
		CreateDirect2DEffectObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_2D_BRUSH_OBJECT_FAILED_CHINESE_SIMPLIFIED, tmpstr, 512);
		CreateDirect2DBrushFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_2D_GRADIENT_STOP_COLLECTION_FAILED_CHINESE_SIMPLIFIED, tmpstr, 512);
		CreateDirect2DGradientStopCollectionFailedText = tmpstr;
		LoadString(ApplicationInstance, IDS_DRAW_WINDOW_CONTENTS_FAILED_CHINESE_SIMPLIFIED, tmpstr, 512);
		DrawWindowContentsFailedText = tmpstr;
		LoadString(ApplicationInstance, IDS_PRESENT_WINDOW_CONTENTS_FAILED_CHINESE_SIMPLIFIED, tmpstr, 512);
		PresentWindowContentsFailedText = tmpstr;
		LoadString(ApplicationInstance, IDS_CUDA_SPEEDUP_ENABLED_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		CudaSpeedupEnabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_CUDA_SPEEDUP_DISABLED_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		CudaSpeedupDisabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_OPENCL_SPEEDUP_ENABLED_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		OpenCLSpeedupEnabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_OPENCL_SPEEDUP_DISABLED_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		OpenCLSpeedupDisabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_CUDA_SPEEDUP_ENABLED_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		CudaSpeedupEnabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_INVALID_EVALUATION_COPY_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		CudaSpeedupDisabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_INVALID_EVALUATION_COPY_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		InvalidEvaluationCopyText = tmpstr;
		LoadString(ApplicationInstance, IDS_COM_ERROR_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		ComErrorText = tmpstr;
		LoadString(ApplicationInstance, IDS_OVERFLOW_ERROR_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		OverflowErrorText = tmpstr;
		LoadString(ApplicationInstance, IDS_UNDERFLOW_ERROR_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		UnderflowErrorText = tmpstr;
		LoadString(ApplicationInstance, IDS_FOR_TESTING_PURPOSES_ONLY_TEXT_CHINESE_SIMPLIFIED, tmpstr, 512);
		ForTestingPurposesOnlyText = tmpstr;
		LoadString(ApplicationInstance, IDS_ERROR_WINDOW_CAPTION_CHINESE_SIMPLIFIED, tmpstr, 512);
		ErrorWindowCaption = tmpstr;
		LoadString(ApplicationInstance, IDS_WARNING_WINDOW_CAPTION_CHINESE_SIMPLIFIED, tmpstr, 512);
		WarningWindowCaption = tmpstr;
		LoadString(ApplicationInstance, IDS_INFORMATION_WINDOW_CAPTION_CHINESE_SIMPLIFIED, tmpstr, 512);
		InformationWindowCaption = tmpstr;
		GlobalLanguage = CHINESE_SIMPLIFIED;
		break;
	case ENGLISH:
		LoadString(ApplicationInstance, IDS_WELCOMETEXT_ENGLISH, tmpstr, 512);
		WelcomeText = tmpstr;
		LoadString(ApplicationInstance, IDS_CONTINUE_AND_CREATE_A_NEW_FILE_BUTTON_TEXT_ENGLISH, tmpstr, 512);
		ContinueAndCreateANewFileButtonText = tmpstr;
		LoadString(ApplicationInstance, IDS_CONTINUE_AND_OPEN_EXISTING_FILE_BUTTON_TEXT_ENGLISH, tmpstr, 512);
		ContinueAndOpenExistingFileButtonText = tmpstr;
		LoadString(ApplicationInstance, IDS_SELECT_A_OPTION_TO_CONTINUE_TEXT_ENGLISH, tmpstr, 512);
		SelectAOptionToContinueText = tmpstr;
		LoadString(ApplicationInstance, IDS_CONTINUE_WITHOUT_ANY_OPERATION_BUTTON_TEXT_ENGLISH, tmpstr, 512);
		ContinueWithoutAnyOperationButtonText = tmpstr;
		LoadString(ApplicationInstance, IDS_DESCRIPTION_BAR_NO_ITEMS_SELECTED_TEXT_ENGLISH, tmpstr, 512);
		DescriptionBarNoItemsSelectedText = tmpstr;
		LoadString(ApplicationInstance, IDS_DESCRIPTION_BAR_NEW_FILE_TEXT_ENGLISH, tmpstr, 512);
		DescriptionBarNewFileText = tmpstr;
		LoadString(ApplicationInstance, IDS_DESCRIPTION_BAR_OPEN_EXISTING_FILE_TEXT_ENGLISH, tmpstr, 512);
		DescriptionBarOpenExistingFileText = tmpstr;
		LoadString(ApplicationInstance, IDS_OUT_OF_MEMORY_ERROR_TEXT_ENGLISH, tmpstr, 512);
		OutOfMemoryErrorText = tmpstr;
		LoadString(ApplicationInstance, IDS_LOGIC_ERROR_TEXT_ENGLISH, tmpstr, 512);
		LogicErrorText = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_WRITE_FACTORY_FAILED_TEXT_ENGLISH, tmpstr, 512);
		CreateDirectWriteFactoryFailedText = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_WRITE_TEXT_FORMAT_FAILED_TEXT_ENGLISH, tmpstr, 512);
		CreateDirectWriteTextFormatFailedText = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_3D_DEVICE_OBJECT_FAILED_TEXT_ENGLISH, tmpstr, 512);
		CreateDirect3DDeviceObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_3D_DEVICE_CONTEXT_OBJECT_FAILED_ENGLISH, tmpstr, 512);
		CreateDirect3DDeviceObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_GET_DXGI_ADAPTER_OBJECT_FAILED_ENGLISH, tmpstr, 512);
		CreateDirect3DDeviceContextObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_GET_DXGI_PARENT_OBJECT_FAILED_ENGLISH, tmpstr, 512);
		GetDXGIParentObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_2D_SWAP_CHAIN_OBJECT_FAILED_ENGLISH, tmpstr, 512);
		CreateDirect2DSwapChainObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_GET_DIRECT_2D_SWAP_CHAIN_OBJECT_FAILED_ENGLISH, tmpstr, 512);
		GetDirect2DBufferObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_2D_BITMAP_FROM_DXGI_SURFACE_OBJECT_FAILED_ENGLISH, tmpstr, 512);
		CreateDirect2DBitmapFromDXGISurfaceObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_2D_EFFECT_OBJECT_FAILED_ENGLISH, tmpstr, 512);
		CreateDirect2DEffectObjectFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_2D_BRUSH_OBJECT_FAILED_ENGLISH, tmpstr, 512);
		CreateDirect2DBrushFailed = tmpstr;
		LoadString(ApplicationInstance, IDS_CREATE_DIRECT_2D_GRADIENT_STOP_COLLECTION_FAILED_ENGLISH, tmpstr, 512);
		CreateDirect2DGradientStopCollectionFailedText = tmpstr;
		LoadString(ApplicationInstance, IDS_DRAW_WINDOW_CONTENTS_FAILED_ENGLISH, tmpstr, 512);
		DrawWindowContentsFailedText = tmpstr;
		LoadString(ApplicationInstance, IDS_PRESENT_WINDOW_CONTENTS_FAILED_ENGLISH, tmpstr, 512);
		PresentWindowContentsFailedText = tmpstr;
		LoadString(ApplicationInstance, IDS_CUDA_SPEEDUP_ENABLED_TEXT_ENGLISH, tmpstr, 512);
		CudaSpeedupEnabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_CUDA_SPEEDUP_DISABLED_TEXT_ENGLISH, tmpstr, 512);
		CudaSpeedupDisabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_OPENCL_SPEEDUP_ENABLED_TEXT_ENGLISH, tmpstr, 512);
		OpenCLSpeedupEnabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_OPENCL_SPEEDUP_DISABLED_TEXT_ENGLISH, tmpstr, 512);
		OpenCLSpeedupDisabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_CUDA_SPEEDUP_ENABLED_TEXT_ENGLISH, tmpstr, 512);
		CudaSpeedupEnabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_INVALID_EVALUATION_COPY_TEXT_ENGLISH, tmpstr, 512);
		CudaSpeedupDisabledText = tmpstr;
		LoadString(ApplicationInstance, IDS_INVALID_EVALUATION_COPY_TEXT_ENGLISH, tmpstr, 512);
		InvalidEvaluationCopyText = tmpstr;
		LoadString(ApplicationInstance, IDS_COM_ERROR_TEXT_ENGLISH, tmpstr, 512);
		ComErrorText = tmpstr;
		LoadString(ApplicationInstance, IDS_OVERFLOW_ERROR_TEXT_ENGLISH, tmpstr, 512);
		OverflowErrorText = tmpstr;
		LoadString(ApplicationInstance, IDS_UNDERFLOW_ERROR_TEXT_ENGLISH, tmpstr, 512);
		UnderflowErrorText = tmpstr;
		LoadString(ApplicationInstance, IDS_FOR_TESTING_PURPOSES_ONLY_TEXT_ENGLISH, tmpstr, 512);
		ForTestingPurposesOnlyText = tmpstr;
		LoadString(ApplicationInstance, IDS_ERROR_WINDOW_CAPTION_ENGLISH, tmpstr, 512);
		ErrorWindowCaption = tmpstr;
		LoadString(ApplicationInstance, IDS_WARNING_WINDOW_CAPTION_ENGLISH, tmpstr, 512);
		WarningWindowCaption = tmpstr;
		LoadString(ApplicationInstance, IDS_INFORMATION_WINDOW_CAPTION_ENGLISH, tmpstr, 512);
		InformationWindowCaption = tmpstr;
		GlobalLanguage = ENGLISH;
		break;
	default:
		throw InvalidLanguage();
	}
}