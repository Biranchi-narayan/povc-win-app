//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

//
// Scenario2.xaml.cpp
// Implementation of the Scenario2 class
//

#include "pch.h"
#include "Scenario2_SelectInternalGif.xaml.h"
#include "pov.h"

using namespace SDKTemplate;

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

Scenario2::Scenario2()
{
    InitializeComponent();
    rootPage = MainPage::Current;
    PickFilesButton->Click += ref new RoutedEventHandler(this, &Scenario2::PickFilesButton_Click);
}

void Scenario2::PickFilesButton_Click(Object^ sender, RoutedEventArgs^ e)
{
	// Clear previous returned file name, if it exists, between iterations of this scenario
	OutputTextBlock->Text = "";

	FileOpenPicker^ openPicker = ref new FileOpenPicker();
	openPicker->ViewMode = PickerViewMode::Thumbnail;
	openPicker->SuggestedStartLocation = PickerLocationId::PicturesLibrary;
	openPicker->FileTypeFilter->Append(".jpg");
	//openPicker->FileTypeFilter->Append(".jpeg");
	//openPicker->FileTypeFilter->Append(".png");

	create_task(openPicker->PickSingleFileAsync()).then([this](StorageFile^ file)
	{
		if (file)
		{
			pov povc;
			int i = povc.send((file->Name)->Data());
			if (i == 1) OutputTextBlock->Text = "Command file cannot be opened";
			else if (i==2) OutputTextBlock->Text = "Previous command not completed";
			else OutputTextBlock->Text = "Selected internal GIF: " + file->Name;
		}
		else
		{
			OutputTextBlock->Text = "Operation cancelled.";
		}
	});
}

