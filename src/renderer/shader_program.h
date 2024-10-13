#pragma once

typedef struct {
	unsigned int ID;
} ShaderProgram;

void load_glsl_shader(const char* vertexPath, const char* fragmentPath, ShaderProgram& program);
void use_shader_program(const ShaderProgram& program);
void delete_shader_program(const ShaderProgram& program);

void shader_uploda_float(const ShaderProgram& program, const char* name, float v);
void shader_upload_vec2(const ShaderProgram& program, const char* name, float x, float y);
void shader_upload_vec4(const ShaderProgram& program, const char* name, float x, float y, float z, float w);