
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
 * \file spriteedit.doc.hpp
 * \brief Contient la doc de la classe sdl::SpriteEditor.
 */

/*!
 * \class sdl::SpriteEditor
 * \brief Fournit une interface pour modifier depuis le programme une sdl::ASprite.
 */

/*!
 * \typedef std::vector<AABB>::iterator saabbs_it
 * \brief Itérateur sur les sous AABBs.
 */

/*!
 * \fn sdl::SpriteEditor::SpriteEditor(SpriteFile* file, std::string id)
 * \brief Construit l'editeur à partir du ASprite ayant pour nom id dans le sdl::SpriteFile file.
 * \param file Le sdl::Spritefile à utiliser.
 * \param id Le nom du sprite à charger.
 */

/*!
 * \fn SpriteEditor& sdl::SpriteEditor::set(SpriteFile* file, std::string id)
 * \brief Définit l'editeur à partir du sdl::ASprite ayant pour nom id dans le sdl::SpriteFile file.
 * \param file Le sdl::Spritefile à utiliser.
 * \param id Le nom du sprite à charger.
 * \return Une référence sur l'éditeur appelant.
 */

/*!
 * \fn SpriteEditor& sdl::SpriteEditor::clear()
 * \brief Remet l'éditeur à zéro.
 * \return Une référence sur l'éditeur appelant.
 */

/*!
 * \fn std::vector<std::string> sdl::SpriteEditor::groups() const
 * \brief Donne la liste des groupes de sous AABBs.
 * \return Le liste des groupes de sous AABBs.
 */

/*!
 * \fn size_t sdl::SpriteEditor::nbGroups() const
 * \brief Donne le nombre de groupes.
 * \return Le nombre de groupes.
 */

/*!
 * \fn bool sdl::SpriteEditor::setCurrent(std::string cur, size_t idx=0)
 * \brief Change le groupe et la sous AABB courante.
 * \param cur Le nouveau groupe courrant.
 * \param idx La nouvelle sous AABB courante.
 * \return Indique si le groupe et la sous AABB on pu être changés.
 */

/*!
 * \fn std::string sdl::SpriteEditor::current() const
 * \brief Indique le groupe courrant.
 * \return Le groupe courrant.
 */

/*!
 * \fn size_t sdl::SpriteEditor::currentIdx() const
 * \brief Indique la sous AABB courrante.
 * \return L'index de la sous AABB courrante.
 */

/*!
 * \fn bool sdl::SpriteEditor::deleteCurrent()
 * \brief Supprime la sous AABB courrante.
 * \return Indique si la sous AABB courrante a pu être supprimée.
 */

/*!
 * \fn bool sdl::SpriteEditor::deleteCurrentGroup()
 * \brief Supprime le groupe courrant.
 * \return Indique si le groupe courrant a pu être supprimé.
 */

/*!
 * \fn AABB sdl::SpriteEditor::get() const
 * \brief Donne la sous AABB courrante.
 * \return La sous AABB courrant.
 */

/*!
 * \fn std::vector<AABB> sdl::SpriteEditor::getGroup() const
 * \brief Donne la liste des sous AABBs du groupe courrant.
 * \return La liste des sous AABBs du groupe courrant.
 */

/*!
 * \fn bool sdl::SpriteEditor::setPriority(int newp)
 * \brief Change la priorité du groupe courrant.
 * \param newp La nouvelle priorité du groupe courrant.
 * \return Indique si la priorité a pu être changée.
 */

/*!
 * \fn int sdl::SpriteEditor::getPriority()
 * \brief Indique la priorité du groupe courrant.
 * \return La priorité du groupe courrant.
 */

/*!
 * \fn saabbs_it sdl::SpriteEditor::SAABBbegin()
 * \brief Retourne l'itérateur de départ sur les sous AABBs du groupe courrant.
 * \return L'itérateur de départ.
 */

/*!
 * \fn saabbs_it sdl::SpriteEditor::SAABBend()
 * \brief Retourne l'itérateur de fin sur les sous AABBs du groupe courrant.
 * \return L'itérateur de fin.
 */

/*!
 * \fn bool sdl::SpriteEditor::modifie(const AABB& nvalue)
 * \brief Change la valeur de la sous AABB courrante.
 * \param nvalue La nouvelle valeur de la sous AABB courrante.
 * \return Indique si la valeur de la sous AABB courrante a pu être changée.
 */

/*!
 * \fn bool sdl::SpriteEditor::modifie(std::string str, size_t idx, const AABB& nvalue)
 * \brief Modifie une sous AABB en particulier.
 * \param str Le nom du groupe dont on veut modifier une sous AABB.
 * \param idx L'index de la sous AABB voulue.
 * \param nvalue La nouvelle valeur de la sous AABB.
 * \return Indique si la valeur de la sous AABB a pu être changée.
 */

/*!
 * \fn size_t sdl::SpriteEditor::nbSAABBS() const
 * \brief Indique le nombre de sous AABBs dans le groupe courrant.
 * \return Le nombre de sous AABBs dans le groupe courrant.
 */

/*!
 * \fn std::vector<AABB> sdl::SpriteEditor::SAABBS() const
 * \brief Donne les sous AABBs du groupe courrant.
 * \return La liste des sous AABBs du groupe courrant.
 */

/*!
 * \fn AABB& sdl::SpriteEditor::operator[](size_t idx)
 * \brief Permet un accès direct à une sous AABB dans le groupe courrant.
 * \param idx L'index de la sous AABB voulue.
 * \return Une référence sur la sous AABB voulue.
 */

/*!
 * \fn std::vector<AABB>& sdl::SpriteEditor::operator[](std::string str)
 * \brief Permet un accès direct à la liste de sous AABBs d'un groupe.
 * \param str Le groupe dont on veut la liste de sous AABBs.
 * \return La liste de sous AABBs du groupe voulu.
 */

/*!
 * \fn void sdl::SpriteEditor::setHotPoint(const Pointsi& hp)
 * \brief Change le point chaud du sprite.
 * \param hp La nouvelle valeur du point chaud.
 */

/*!
 * \fn bool sdl::SpriteEditor::addGroup(std::string gr)
 * \brief Ajoute un nouveau groupe.
 * \param gr Le nom du nouveau groupe.
 * \return Indique si le groupe a pu être ajouté.
 */

/*!
 * \fn bool sdl::SpriteEditor::deleteGroup(std::string str)
 * \brief Supprime un groupe.
 * \param str Le nom du groupe à supprimer.
 * \return Indique si le groupe a pu être supprimé.
 */

/*!
 * \fn bool sdl::SpriteEditor::addSAABB(const AABB& saabb)
 * \brief Ajoute une sous AABB au groupe courrant.
 * \param saabb La nouvelle sous AABB.
 * \return Indique si la sous AABB a pu être ajoutée.
 */

/*!
 * \fn bool sdl::SpriteEditor::deleteSAABB(size_t idx)
 * \brief Supprime une sous AABB dans le groupe courrant.
 * \param idx L'index de la sous AABB à supprimer.
 * \return Indique si la sous AABB a pu être supprimée.
 */

/*!
 * \fn Pointsi sdl::SpriteEditor::hotpoint() const
 * \brief Indique le point chaud.
 * \return Le point chaud.
 */

/*!
 * \fn SDL_Surface* sdl::SpriteEditor::getReal()
 * \brief Donne la SDL_Surface uitlisée.
 * \return La SDL_Surface utilisée.
 */

/*!
 * \fn ASprite sdl::SpriteEditor::tmpSprite() const
 * \brief Donne le sprite en construction. Non utilisable mais permet d'avoir des informations.
 * \return Le sprite en construction.
 */

/*!
 * \fn ASprite* sdl::SpriteEditor::operator->()
 * \brief Donne un pointeur sur le sprite en construction. Non utilisable mais permet d'avoir des informations.
 * \return Un pointeur sur le sprite en construction.
 */

/*!
 * \fn bool sdl::SpriteEditor::save(const ASprite::path_t& path) const
 * \brief Sauvegarde le sprite créé.
 * \param path Le chemin de la sauvegarde.
 * \return Indique si la sauvegarde a réussi.
 */

/*!
 * \fn ASprite sdl::SpriteEditor::create() const
 * \brief Crée un sdl::ASprite utilisable.
 * \return Le sdl::ASprite utilisable.
 */

/*!
 * \fn bool sdl::SpriteEditor::check() const
 * \brief Indique si la classe est utilisable (si un sprite a été chargé).
 * \return Si la classe est utilisable.
 */

/*!
 * \fn sdl::SpriteEditor::operator bool() const
 * \brief Indique si la classe est utilisable (si un sprite a été chargé).
 * \return Si la classe est utilisable.
 */

/*!
 * \fn bool sdl::SpriteEditor::operator!() const
 * \brief Indique si la classe est utilisable (si un sprite a été chargé).
 * \return Si la classe n'est pas utilisable.
 */




