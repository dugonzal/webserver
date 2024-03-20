#include "../Utils.hpp"

class ClientSide {
	private:
    /* Client Server Side */
    int							clientFd;
    struct sockaddr_in			clientAddr; // IP socket address
    socklen_t					addrClientLen;

	/* Client Message Side */
    int							returnedBytes;
	std::string					askedRoute;
    char						clientMsg[1028];
	std::string					serverResponse; // Header for Client
    struct  timeval				timeout;

    // Variables Iker
    std::string method, file;

	public:
		ClientSide( void );
		ClientSide( int _serverFd );
		~ClientSide( void );

		int 	openFile( std::string _route );
		void	setRoute( void );
        std::string	ClientSide::getRoute( void );

    // Funciones Iker
        void    getMethod( void );
        void    postMethod( void );
        void    deleteMethod( void );
        void    response2client( void );


};