CC=gcc
FLAGS= 
FILES= main.c tools.c ft_lexer.c check_syntax.c parser.c check_command.c ft_split.c expander.c ft_riderct.c
OBJS= $(FILES:.c=.o)
NAME= minishell
INCLUDES=-I minishell.h -I /goinfre/snouae/.brew/opt/readline/include
READLINE=-lreadline -L/goinfre/snouae/.brew/opt/readline/lib
RM= rm -rf

all: $(NAME) clean

$(NAME): $(OBJS) 
	$(CC) $(FLAGS) $^ $(READLINE)  -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
