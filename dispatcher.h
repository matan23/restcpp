#ifndef ROUTER_H_
# define ROUTER_H_

void		dispatch(std::string &method, std::string &url, std::string &content);

typedef	struct	s_route {
  char*		str;
  void		(*ptr)(std::string &url, std::string &content);
}								t_route;

void	post_method(std::string &url, std::string &content);
void	put_method(std::string &url, std::string &content);
void	delete_method(std::string &url, std::string &content);
void	get_method(std::string &url, std::string &content);
void	patch_method(std::string &url, std::string &content);


#endif	// !__ROUTER__
