#include <efi.h>
#include <efilib.h>


EFI_FILE* load_file(EFI_FILE* directory, CHAR16* path, EFI_HANDLE image_handle, EFI_SYSTEM_TABLE* system_table)
{
	EFI_FILE* loaded_file;
	EFI_LOADED_IMAGE_PROTOCOL* loaded_image;
	system_table->BootServices->HandleProtocol(image_handle, &gEfiLoadedImageProtocolGuid, (void**)&loaded_image);

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *file_system;
	system_table->BootServices->HandleProtocol(loaded_image->DeviceHandle, &gEfiLoadedImageProtocolGuid, (void**)&file_system);

	if (directory == NULL)
	{
		file_system->OpenVolume(file_system, &directory);
	}

	EFI_STATUS s = directory->Open(directory, &loaded_file, path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if (s != EFI_SUCCESS)
	{
		return NULL;
	} 
	return loaded_file;
}


EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {

	InitializeLib(ImageHandle, SystemTable);
	Print(L"String just testing \n\r");

	if (load_file(NULL, L"kernel.elf", ImageHandle, SystemTable) == NULL)
	{
		Print(L"Could not load kernel");
	}
	else 
	{
		Print(L"Kernel loaded successfully");

	}

	return EFI_SUCCESS; // Exit the UEFI application
}
