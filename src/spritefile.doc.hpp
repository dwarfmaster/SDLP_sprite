
/*
 * Copyright (C) 2012 Chabassier Luc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*!
 * \file spritefile.doc.hpp
 * \brief Contient la doc de la classe sdl::SpriteFile.
 */

/*!
 * \class sdl::SpriteFile
 * \brief Sert à charger et sauvegarder des fichiers de sprite. 
 *
 * Voir le fichier example.sprite pour la syntaxe de ces derniers.
 */

/*!
 * \typedef boost::filesystem::path sdl::SpriteFile::path_t
 * \brief Le type de chemin utilisé.
 */

/*!
 * \typedef std::map<std::string, sprite>::iterator sdl::SpriteFile::sprite_iterator
 * \brief Un itérateur pour parcourir les sprites stockées.
 */

/*!
 * \typedef std::map<std::string, sprite>::const_iterator sdl::SpriteFile::csprite_iterator
 * \brief Un itérateur constant pour parcourir les sprites stockées.
 */

/*!
 * \fn sdl::SpriteFile::SpriteFile(const path_t& path)
 * \brief Charge le fichier au chemin path.
 * \param path Le chemin à charger.
 */

/*!
 * \fn void sdl::SpriteFile::clear()
 * \brief Vide et libère le contenu de la classe.
 */

/*!
 * \fn bool sdl::SpriteFile::load(const path_t& path)
 * \brief Charge le fichier au chemin path.
 * \param path Le chemin à charger.
 * \return Un booléen indiquant si le chemin a pu être chargé.
 */

/*!
 * \fn ASprite sdl::SpriteFile::getSprite(std::string id)
 * \brief Donne la sprite ayant pour nom id.
 * \param id Le nom de la sprite voulue.
 * \return Le sprite voulue. Une sprite vide si id est inexistant.
 */

/*!
 * \fn AABB sdl::SpriteFile::getRect(std::string id) const
 * \brief Donne la partie de image utilisée par le sprite.
 * \param id Le nom de la sprite dont on veut le rect.
 * \return Le rect de la sprite. Un rect vide si id est invalide.
 */

/*!
 * \fn ASprite sdl::SpriteFile::operator[](std::string id)
 * \brief Donne la sprite ayant pour nom id.
 * \param id Le nom de la sprite voulue.
 * \return Le sprite voulu. Une sprite vide si id est inexistant.
 */

/*!
 * \fn bool sdl::SpriteFile::exist(std::string id) const
 * \brief Indique si le sprite ayant pour nom id existe.
 * \param id Le nom du sprite à tester.
 * \return Un booléen indiquant si le sprite existe.
 */

/*!
 * \fn std::vector<std::string> sdl::SpriteFile::listIds() const
 * \brief Liste les sprite existants.
 * \return La liste des sprites existant.
 */

/*!
 * \fn bool sdl::SpriteFile::changeSprite(std::string id, const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const AABB& rect)
 * \brief Modifie une sprite.
 * \param id Le nom de la sprite à modifier.
 * \param groups Les nouveaux groupes de sous AABBs.
 * \param hotp Le nouveau point chaud.
 * \param rect Le nouveau rect (partie de l'image).
 * \return Indique si la sprite a pu être modifiée.
 */

/*!
 * \fn bool sdl::SpriteFile::changeSprite(std::string id, const std::map<std::string, gaabb>& groups, const Pointsi& hotp)
 * \param id Le nom de la sprite à modifier.
 * \param groups Les nouveaux groupes de sous AABBs.
 * \param hotp Le nouveau point chaud.
 * \return Indique si la sprite a pu être modifiée.
 */

/*!
 * \fn bool sdl::SpriteFile::addSprite(std::string id, const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const AABB& rect)
 * \brief Ajoute une sprite.
 * \param id Le nom de la sprite à ajouter.
 * \param groups Les groupes de sous AABBs.
 * \param hotp Le point chaud.
 * \param rect Le rect (partie de l'image).
 * \return Indique si la sprite a pu être ajoutée.
 */

/*!
 * \fn bool sdl::SpriteFile::deleteSprite(std::string id)
 * \brief Supprime une sprite.
 * \param id Le nom de la sprite à supprimer.
 * \return Indique si la sprite a pu être supprimée.
 */

/*!
 * \fn bool sdl::SpriteFile::save(path_t path) const
 * \brief Sauvegarde le SpriteFile dans le fichier path.
 * \param path Le chemin de sauvegarde.
 * \return Indique si le SpriteFile a pu être sauvegardé.
 */

/*!
 * \fn bool sdl::SpriteFile::save() const
 * \brief Sauvegarde le SpriteFile dans le même fichier qui avait été chargé.
 * \return Indique si le SpriteFile a pu être sauvegardé.
 */

/*!
 * \fn static std::string sdl::SpriteFile::xmlSprite(const ASprite& sprite, const std::string& id, const AABB& rect, const std::string& toadd="", const std::string& begin="")
 * \brief Convertit un sprite en code xml.
 * \param sprite Le sprite à convertir.
 * \param id Le nom à lui donner dans l'xml.
 * \param rect La partie de l'image qu'il occupe.
 * \param toadd Chaine ajoutée dans la déclaration du sprite.
 * \param begin Chaine ajoutée au début de chaque ligne.
 * \return Le code xml dans une std::string.
 */

/*!
 * \fn static ASprite* sdl::SpriteFile::spriteXml(TiXmlElement* sprite, const path_t& img, AABB* rect = NULL)
 * \brief Convertit un fichier xml en sprite.
 * \param sprite Le node xml à parser.
 * \param img Le chemin de l'image à charger.
 * \param rect La partie de l'image occupée par le futur sprite. S'il vaut NULL, celui précisé dans l'xml sera utilisé.
 * \return L'ASprite créé. Le pointeur devra être libéré.
 */

/*!
 * \fn static ASprite* sdl::SpriteFile::spriteXml(TiXmlElement* sprite, SDL_Surface* img, AABB* arect = NULL)
 * \brief Convertit un fichier xml en sprite.
 * \param sprite Le node xml à parser.
 * \param img L'image à utiliser.
 * \param rect La partie de l'image occupée par le futur sprite. S'il vaut NULL, celui précisé dans l'xml sera utilisé.
 * \return L'ASprite créé. Le pointeur devra être libéré.
 */

/*!
 * \struct sdl::SpriteFile::sprite
 * \brief Stocke un sprite temporaire.
 */

/*!
 * \fn static bool sdl::SpriteFile::parseSprite(TiXmlElement* spriten, sprite* p, const SDL_Surface* img)
 * \brief Parse un sprite et le stocke dans p.
 * \param spriten Le node xml à parser.
 * \param p Le sprite dans lequel est stocké ce qui est chargé.
 * \param img L'image, utilisée pour des vérifications lors du chargement du rect.
 * \return Indique si il y a eu une erreur lors du parsage.
 */

/*!
 * \fn static void sdl::SpriteFile::parseRect(TiXmlElement* spriten, AABB* p, const SDL_Surface* img)
 * \brief Parse le rect du sprite.
 * \param spriten Le node sprite dont le rect doit être parsé.
 * \param p L'AABB dans laquel est stocké le rect.
 * \param img L'image, utilisée pour des vérifications lors du chargement du rect.
 * \return Indique si il y a eu une erreur lors du parsage.
 */

/*!
 * \fn static bool sdl::SpriteFile::parseGAABB(TiXmlElement* gaabbn, gaabb* p)
 * \brief Parse un groupe de sous AABBs.
 * \param gaabbn Le node du groupe à parser.
 * \param p Le groupe dans lequel sont stockées les données chargées.
 * \return Indique si il y a eu une erreur lors du parsage.
 */


