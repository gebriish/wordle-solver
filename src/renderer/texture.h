#pragma once
#include <cstdint>

struct Texture {
	unsigned int ID;
	const uint16_t width;
	const uint16_t height;
};

Texture load_texture(const char* path);
void bind_texture(const Texture& texture, uint64_t slot);
void delete_texture(const Texture& texture);