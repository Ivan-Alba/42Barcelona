#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <string>

class Brain
{
	private:
		std::string ideas[100];
	
	public:
		Brain();
		Brain(const Brain &other);
		Brain& operator=(const Brain &other);
		~Brain();

		std::string	getIdea(int idx) const;
		void		setIdea(int idx, const std::string &idea);
};

#endif
