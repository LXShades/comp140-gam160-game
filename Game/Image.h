#pragma once
#include "Math.h"
#include "String.h"

class Image {
public:
	// Constructor: Empty image
	Image() : pixels(nullptr), pitch(0), dimensions(0, 0), filename("") {
		// Add global ref
		Image::AddRef();
	};

	// Constructor: Loads image from a file
	Image(const char* filename);

	// Copy constructor
	Image(const Image& other);

	// Destructor: Frees and dereferences image information
	~Image();

public:
	// Loads a new image, discarding any previous data
	bool Load(const char* filename);

	// Returns whether the image was successfully loaded
	inline bool IsLoaded() const;

	// Returns the original file name
	inline const char* GetFilename() const;

public:
	// Returns the dimensions of the image
	inline const Dimensions2& GetDimensions() const;

	// Returns the number of bytes per row
	inline int GetPitch() const;

	// Returns the raw pixels as uint32s in the format AARRGGBB
	inline const uint32* GetPixelDataARGB() const;

public:
	// Returns a new SDL texture based on this image. This texture is not bound to this image and must be freed by the caller
	struct SDL_Texture* CreateSDLTexture(struct SDL_Renderer* renderer) const;

protected:
	// Raw pixel data, if successfully loaded
	uint32* pixels;

	// Image dimensions
	Dimensions2 dimensions;

	// Number of bytes per row
	int32 pitch;

	// Name of the file used to load the image (used to save maps)
	StaticString<260 /* MAX_PATH w/o including Windows.h */> filename;

	// Reference counting: Called by the constructor to initialize and deinitialize Gdiplus when needed
	static void AddRef();
	static void RemoveRef();

	static int32 numRefs;
};

inline bool Image::IsLoaded() const {
	// If pixels were never loaded, it's fair to say no image was loaded (or the programmer loaded an empty image--but why!?)
	return pixels != nullptr;
}

inline const char* Image::GetFilename() const {
	return filename;
}

inline const Dimensions2& Image::GetDimensions() const {
	return dimensions;
}

inline const uint32* Image::GetPixelDataARGB() const {
	return pixels;
}