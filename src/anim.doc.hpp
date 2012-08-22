
/*!
 * \file anim.doc.hpp
 * \brief Contient la doc de sdl::Anim.
 */

/*!
 * \class sdl::Anim
 * \brief Manipule des animations.
 *
 * Les animations sont chargées depuis des fichier xml. Voir le fichier example.anim pour plus d'information sur la syntaxe de ces fichiers.
 */


/*!
 * \fn sdl::Anim::Anim(const path_t& path)
 * \brief Construit l'anim à partir d'un fichier.
 * \param path Le chemin du fichier.
 */

/*!
 * \fn void sdl::Anim::clear()
 * \brief Vide l'anim.
 */

/*!
 * \fn bool sdl::Anim::load(const path_t& path)
 * \brief Charge l'anim depuis un fichier.
 * \param path Le chemin du fichier.
 * \return Indique si le fichier a pu être chargé.
 */

/*!
 * \fn bool sdl::Anim::save(const path_t& path)
 * \brief Sauvegarde l'anim dans un fichier.
 * \param path Le chemin du fichier.
 * \return Indique si le chemin a pu être sauvegardé.
 */

/*!
 * \fn bool sdl::Anim::isLoaded() const
 * \brief Indique si l'anim est chargée et donc utilisable.
 * \return Si l'anim est chargée.
 */

/*!
 * \fn sdl::Anim::operator bool() const
 * \brief Indique si l'anim est chargée et donc utilisable.
 * \return Si l'anim est chargée.
 */

/*!
 * \fn bool sdl::Anim::operator!() const
 * \brief Indique si l'anim est chargée et donc utilisable.
 * \return Si l'anim n'est pas chargée.
 */

/*!
 * \fn std::vector<std::string> sdl::Anim::frames() const
 * \brief Indique les frames disponibles.
 * \return La liste des noms des frames disponibles.
 */

/*!
 * \fn size_t sdl::Anim::nbFrames() const
 * \brief Indique le nombre de frames disponibles.
 * \return Le nombre de frames disponibles.
 */

/*!
 * \fn size_t sdl::Anim::idFromName(const std::string& name) const
 * \brief Donne l'id d'une frame à partir de son nom.
 * \param name Le nom de la frame voulue.
 * \return L'id de la frame voulue. Si name est inexistant, une valeur supérieur ou égale à sdl::Anim::nbFrames sera retournée.
 */

/*!
 * \fn std::string sdl::Anim::nameFromId(size_t id) const
 * \brief Donne le nom d'une frame à partir de son id.
 * \param id L'id de la frame voulue.
 * \return Le nom de la frame voulue. Si l'id est invalide, une exception est lancée.
 */

/*!
 * \fn ASprite* sdl::Anim::sprite(const std::string& frame) const
 * \brief Donne un pointeur sur la sdl::ASprite appartenant une frame.
 * \param frame Le nom de la frame voulue.
 * \return Le pointeur sur la sdl::ASprite correspondante. Lance une exception si le nom est invalide.
 */

/*!
 * \fn ASprite* sdl::Anim::operator[](const std::string& frame) const
 * \brief Donne un pointeur sur la sdl::ASprite appartenant une frame.
 * \param frame Le nom de la frame voulue. Lance une exception si le nom est invalide.
 * \return Le pointeur sur la sdl::ASprite correspondante.
 */

/*!
 * \fn Uint32 sdl::Anim::time(const std::string& frame) const
 * \brief Indique le temps que dure une frame.
 * \param frame Le nom de la frame voulue. Lance une exception si le nom est invalide.
 * \return La durée de la frame.
 */

/*!
 * \fn Uint32 sdl::Anim::time() const
 * \brief Indique le temps total de l'anim.
 * \return Le temps total de l'anim.
 */

/*!
 * \fn Uint32 sdl::Anim::defaultTime() const
 * \brief Indique le temps par défaut pour les frames.
 * \return Le temps par défaut pour les frames.
 */

/*!
 * \fn bool sdl::Anim::changeSprite(const std::string& frame, ASprite* nsprite, bool tofree=false)
 * \brief Modifie une frame.
 * \param frame Le nom de la frame à modifier.
 * \param nsprite La nouvelle valeur.
 * \param tofree Indique s'il faudra libérer la sdl::ASprite.
 * \return Indique si la sprite a pu être modifiée.
 */

/*!
 * \fn bool sdl::Anim::changeTime(const std::string& frame, Uint32 ntime)
 * \brief Change le temps d'une frame.
 * \param frame Le nom de la frame à changer.
 * \param ntime Le nouveau temps de la frame.
 * \return Indique si le temps a pu être changé.
 */

/*!
 * \fn bool sdl::Anim::reorder(const std::vector<std::string>& norder)
 * \brief Réorganise les sprites.
 * \param norder Doit contenir la liste des noms de frames dan l'ordre voulu.
 * \return Indique si l'ordre a pu être changé.
 */

/*!
 * \fn bool sdl::Anim::addFrame(size_t pos, const std::string& name, ASprite* sprite,  Uint32 time=0, bool tofree=false, AABB rect = makeRect(0,0,0,0), path_t path = "")
 * \brief Ajoute une frame.
 * \param pos La position de la nouvelle frame.
 * \param name Le nom de la nouvelle frame.
 * \param sprite La sdl::ASprite de la nouvelle sprite. Ne sera pas copié.
 * \param time Le temps de la nouvelle sprite. S'il vaut zéro, le temps par défaut sera appliqué.
 * \param tofree S'il faudra libérer la sprite.
 * \param rect Sert uniquement d'indication sur la portion de l'image originale occupée par le sprite pour la sauvegarde.
 * \param path Sert uniquement d'indication sur le chemin de l'image originale pour la sauvegarde.
 * \return Indique si la frame a pu être ajoutée.
 */

/*!
 * \fn bool sdl::Anim::deleteFrame(const std::string& name)
 * \brief Supprime une frame.
 * \param name Le nom de la frame à supprimer.
 * \return Indique si la frame a pu être supprimée.
 */

/*!
 * \fn bool sdl::Anim::exist(const std::string& frame) const
 * \brief Indique si une frame existe.
 * \param frame Le nom de la frame à tester.
 * \return Si la frame existe, true.
 */

/*!
 * \fn ASprite* sdl::Anim::update()
 * \brief Met à jour l'anim à partir du temps écoulé depuis le dernier appel.
 * \return La sdl::ASprite correspondant à la frame actuelle.
 */

/*!
 * \fn ASprite* sdl::Anim::getSprite()
 * \brief Donne la sdl::ASprite correspondant à la frame actuelle.
 * \return La sdl::ASprite correspondant à la frame actuelle.
 */

/*!
 * \fn const ASprite* sdl::Anim::getSprite() const
 * \brief Donne la sdl::ASprite correspondant à la frame actuelle.
 * \return La sdl::ASprite correspondant à la frame actuelle.
 */

/*!
 * \fn sdl::Anim::operator ASprite*()
 * \brief Donne la sdl::ASprite correspondant à la frame actuelle.
 * \return La sdl::ASprite correspondant à la frame actuelle.
 */

/*!
 * \fn sdl::Anim::operator const ASprite*() const
 * \brief Donne la sdl::ASprite correspondant à la frame actuelle.
 * \return La sdl::ASprite correspondant à la frame actuelle.
 */

/*!
 * \fn sdl::Anim::operator ASprite() const
 * \brief Donne la sdl::ASprite correspondant à la frame actuelle.
 * \return La sdl::ASprite correspondant à la frame actuelle.
 */

/*!
 * \fn ASprite* sdl::Anim::operator->()
 * \brief Donne la sdl::ASprite correspondant à la frame actuelle.
 * \return La sdl::ASprite correspondant à la frame actuelle.
 */

/*!
 * \fn const ASprite* sdl::Anim::operator->() const
 * \brief Donne la sdl::ASprite correspondant à la frame actuelle.
 * \return La sdl::ASprite correspondant à la frame actuelle.
 */

/*!
 * \fn SDL_Surface* sdl::Anim::getImg() const
 * \brief Donne la SDL_Surface correspondant à la frame actuelle.
 * \return La SDL_Surface correspondant à la frame actuelle.
 */

/*!
 * \fn sdl::Anim::operator SDL_Surface*() const
 * \brief Donne la SDL_Surface correspondant à la frame actuelle.
 * \return La SDL_Surface correspondant à la frame actuelle.
 */

/*!
 * \fn void sdl::Anim::reset()
 * \brief Remet l'anim au début de la première frame.
 */

/*!
 * \fn void sdl::Anim::set(const std::string& frame)
 * \brief Met l'anim au début d'une frame.
 * \param frame Le nom de la frame voulue.
 */

/*!
 * \fn void sdl::Anim::set(size_t id)
 * \brief Met l'anim au début d'une frame.
 * \param id L'id de la frame voulue.
 */

/*!
 * \fn void sdl::Anim::pause()
 * \brief Met l'anim en pause.
 */

/*!
 * \fn void sdl::Anim::play()
 * \brief Joue l'anim.
 */

/*!
 * \fn void sdl::Anim::next()
 * \brief Passe au début de la frame suivante.
 */

/*!
 * \fn void sdl::Anim::prev()
 * \brief Passe au début de la frame précédente.
 */

/*!
 * \fn void sdl::Anim::forward(Uint32 time)
 * \brief L'animation avance d'un certain temps.
 * \param time Le temps à avancer.
 */

/*!
 * \fn void sdl::Anim::backward(Uint32 time)
 * \brief L'animation recule d'un certain temps.
 * \param time Le temps à reculer.
 */

/*!
 * \fn void sdl::Anim::speed(float nspeed=1.0)
 * \brief Définit un facteur de vitesse pour l'animation.
 * \param nspeed La nouveau facteur de vitesse.
 */

/*!
 * \fn std::string sdl::Anim::getActName() const
 * \brief Donne le nom de la frame actuelle.
 * \return Le nom de la frame actuelle.
 */

/*!
 * \fn size_t sdl::Anim::getActId() const
 * \brief Donne l'id de la frame actuelle.
 * \return L'id de la frame actuelle.
 */

/*!
 * \fn sdl::AABB sdl::Anim::getMaxSize() const
 * \brief Indique la taille maximum que peuvent prendre les frames.
 * \return La taille maximum.
 */

/*!
 * \fn sdl::AABB sdl::Anim::getMaxSizeFloat() const
 * \brief Indique la taille maximum que peuvent prendre les frames en considérant que leur point chaud est statique.
 * \return La taille maximum avec un point chaud statique.
 */

/*!
 * \fn void sdl::Anim::parseSprites(std::vector<frame>* sprites, TiXmlElement* elem, path_t basepath)
 * \brief Parse un nœud xml.
 * \param sprites Un pointeur sur un tableau dans lequel seront stockées les donnés parsées.
 * \param elem Le nœud xml à parser.
 * \param basepath Chemin de base à ajouter aux chemin parsés.
 */

/*!
 * \typedef std::vector<frame>::iterator sdl::Anim::frame_iterator
 * \brief Itérateur servant à parcourir les frames.
 */

/*!
 * \typedef std::vector<frame>::const_iterator sdl::Anim::cframe_iterator
 * \brief Itérateur constant servant à parcourir les frames.
 */

/*!
 * \struct sdl::Anim::frame
 * \brief Stocke une frame de l'animation.
 */


