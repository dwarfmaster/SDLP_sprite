
/*!
 * \file asprite.doc.hpp
 * \brief Contient la doc de la classe sdl::ASprite.
 */

/*!
 * \namespace sdl
 * \brief Contient les fonctions des bibliothèques SDLP_qqchose.
 */

/*!
 * \struct sdl::gaabb
 * \brief Utilisé pour la création de ASprite par SpriteFile.
 *
 * Ne doit pas être utilisé par un utilisateur de la bibliothèque. Réservé à un usage interne.
 */

/*!
 * \class sdl::ASprite
 * \brief Stocke et manipule une image avec des informations de colision et de blit.
 *
 * Pour en charger une, voir la classe sdl::SpriteFile, et pour en modifier une, voir la classe sdl::SpriteEditor.
 */

/*!
 * \struct sdl::ASprite::GAABB
 * \brief Stocke un groupe de sous AABBs.
 */

/*!
 * \typedef std::map<std::string,GAABB>::iterator sdl::ASprite::group_iterator
 * \brief Itérateur utilisé pour parcourir les groupes.
 */

/*!
 * \typedef std::map<std::string,GAABB>::const_iterator sdl::ASprite::c_group_iterator
 * \brief Itérateur constant utilisé pour parcourir les groupes.
 */


/*!
 * \typedef boost::filesystem::path sdl::ASprite::path_t
 * \brief Le type de chemin utilisé.
 */

/*!
 * \fn sdl::ASprite::ASprite(const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const boost::shared_ptr<SDL_Surface>& img)
 * \brief Constructeur utilisé pour la création de ASprite par SpriteFile.
 * \param groups Les groupes de sous AABBs.
 * \param hotp Le point chaud (ou point de blit).
 * \param img La surface à blitter.
 *
 * Ne doit pas être utilisé par un utilisateur de la bibliothèque. Réservé à un usage interne.
 */

/*!
 * \fn void sdl::ASprite::set(const std::map<std::string, gaabb>& groups, const Pointsi& hotp, const boost::shared_ptr<SDL_Surface>& img)
 * \brief Utilisé pour la création de ASprite par SpriteFile.
 * \param groups Les groupes de sous AABBs.
 * \param hotp Le point chaud (ou point de blit).
 * \param img La surface à blitter.
 *
 * Ne doit pas être utilisé par un utilisateur de la bibliothèque. Réservé à un usage interne.
 */

/*!
 * \fn void sdl::ASprite::clear()
 * \brief Libère la classe, notemment la surface.
 */

/*!
 * \fn sdl::ASprite::operator SDL_Surface() const
 * \brief Renvoie l'image utilisée par la classe.
 */

/*!
 * \fn sdl::ASprite::operator boost::shared_ptr<SDL_Surface>()
 * \brief Renvoie l'image utilisée par la classe sous la forme d'un pointeur intelligent.
 */

/*!
 * \fn boost::shared_ptr<SDL_Surface> sdl::ASprite::get() const
 * \brief Renvoie l'image utilisée par la classe.
 * \return L'image utilisée par la classe sous la forme d'un pointeur intelligent.
 */

/*!
 * \fn SDL_Surface* sdl::ASprite::getPtr() const
 * \brief Renvoie l'image utilisée par la classe.
 * \return Un pointeur non sécurisé sur l'image. Ne doit pas être libéré.
 */

/*!
 * \fn Pointsi sdl::ASprite::hotPoint() const
 * \brief Donne le point chaud (de blit) du sprite.
 * \return Le point chaud du sprite.
 */

/*!
 * \fn Vector2f sdl::ASprite::decale() const
 * \brief Indique de combien doit être décalé le coin en haut à gauche de l'image pour que sa position soit sur le point chaud.
 * \return Vecteur indiquant le décalage nécessaire lors du blit pour utiliser le point chaud.
 */

/*!
 * \fn AABB sdl::ASprite::global() const
 * \brief Indique l'AABB englobant toutes les sous AABBs du sprite.
 * \return L'AABB englobant toutes les sous AABBs du sprite.
 */

/*!
 * \fn std::vector<AABB> sdl::ASprite::saabb(std::string id) const
 * \brief Donne les sous AABBs pour un groupe donné.
 * \param id Le nom du groupe. Si ce dernier n'existe pas, un tableau nul sera retourné.
 * \return Les sous AABBs du groupe.
 */

/*!
 * \fn AABB sdl::ASprite::globalSAABB(std::string id) const
 * \brief Indique l'AABB globale pour un groupe donné.
 * \param id Le nom du groupe. si ce dernier n'existe pas, une AABB nule sera retournée.
 * \return L'AABB englobant toutes les sous AABBs du groupe.
 */

/*!
 * \fn std::vector<AABB> sdl::ASprite::operator[](std::string id) const
 * \brief Donne les sous AABBs pour un groupe donné.
 * \param id Le nom du groupe. Si ce dernier n'existe pas, un tableau nul sera retourné.
 * \return Les sous AABBs du groupe.
 */

/*!
 * \fn bool sdl::ASprite::exist(std::string id) const
 * \brief Indique si un groupe existe.
 * \param id Le groupe à tester.
 * \return Un booléen indiquant si le groupe existe.
 */

/*!
 * \fn std::vector<std::string> sdl::ASprite::groups() const
 * \brief Indique les groupe existants.
 * \return La liste des groupes existants.
 */

/*!
 * \fn std::vector<std::string> sdl::ASprite::inGroup(const Pointsi& p) const
 * \brief Teste si un point est à l'intérieur d'un groupe.
 * \param p Le point à tester.
 * \return La liste des groupes contenant le point (c'est à dire à l'intérieur d'une des sous AABBs du groupe).
 */

/*!
 * \fn std::string sdl::ASprite::inUniqueGroup(const Pointsi& p) const
 * \brief Teste si un point est contenu dans un groupe.
 * \param p Le point à tester.
 * \return Le groupe contenant le point. Si plusieurs groupes contiennent le point, celui ayant la priorité la plus élevée sera retourné.
 */

/*!
 * \fn unsigned int sdl::ASprite::priority(std::string id) const
 * \brief Indique la priorité d'un groupe.
 * \param id Le groupe dont on veut la priorité. Si ce dernier n'existe pas, 0 sera retourné.
 * \return Le priorité du groupe.
 */

/*!
 * \fn std::vector< std::pair<std::string, std::string> > sdl::ASprite::colision(Pointsi pos1, const ASprite& other, Pointsi pos2) const
 * \brief Retourne la liste des groupes du sprite appelant qui sont en colision avec les sprite du second.
 * \param pos1 La position du sprite appelant.
 * \param other Le sprite avec qui la colision doit être testée.
 * \param pos2 Le position du sprite other.
 * \return La liste des groupes du sprite appelant qui sont en contact avec les sprites du second (par exemple { {bras,jambe}, {tete,corp} } signifie que le groupe 'bras' du sprite est en contact avec le groupe 'jambe' du sprite other et que le groupe 'tete' du sprite est en contact avec le groupe 'corp' du sprite appelant).
 */

/*!
 * \fn GAABB sdl::ASprite::fromGaabb(const gaabb& cp)
 * \brief Convertit une gaabb en GAABB.
 * \param cp La gaabb à convertir.
 * \return La GAABB créée.
 */


