#include "Material.h"

Material::Material(Vector3 ambient, Vector3 diffuse, Vector3 specular, double shine)  {
	mat_diffuse[0] = diffuse.getX();
	mat_diffuse[1] = diffuse.getY();
	mat_diffuse[2] = diffuse.getZ();
	mat_ambient[0] = ambient.getX();
	mat_ambient[1] = ambient.getY();
	mat_ambient[2] = ambient.getZ();
	mat_specular[0] = specular.getX();
	mat_specular[1] = specular.getY();
	mat_specular[2] = specular.getZ();
	mat_shininess[0] = shine;
}

Material::Material(Vector3 ambient, Vector3 diffuse, Vector3 specular, Vector3 emissive,  double shine) {
	mat_diffuse[0] = diffuse.getX();
	mat_diffuse[1] = diffuse.getY();
	mat_diffuse[2] = diffuse.getZ();
	mat_ambient[0] = ambient.getX();
	mat_ambient[1] = ambient.getY();
	mat_ambient[2] = ambient.getZ();
	mat_specular[0] = specular.getX();
	mat_specular[1] = specular.getY();
	mat_specular[2] = specular.getZ();
	mat_shininess[0] = shine;
	mat_emission[0] = emissive.getX();
	mat_emission[1] = emissive.getY();
	mat_emission[2] = emissive.getZ();
}

void Material::draw() {
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
}
void Material::setMaterialEmissive(Vector3 emissive) {
	mat_emission[0] = emissive.getX();
	mat_emission[1] = emissive.getY();
	mat_emission[2] = emissive.getZ();
}