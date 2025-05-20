/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:22:12 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/04/11 13:19:55 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

extern int			g_signal;
enum				e_token_type
{
	INREDIR,
	OUTREDIR,
	PIPE,
	SPACE_,
	TAB_,
	OPERATOR,
	APPOUTREDIR,
	HEREDOC,
	WORD
};

typedef struct s_utils
{
	int				i;
	int				j;
	int				start;
	int				varname_start;
	int				end;
	int				varname_len;
	int				varcontent_len;
	int				varcontent_start;
	int				env_index;
	char			*varname1;
	char			*varcontent1;
}					t_utils;

typedef struct s_input
{
	char			*linebuffer;
	size_t			nread;
	int				exit_status;
	int				again;
	int				len;
}					t_input;

typedef struct s_lexbuf
{
	struct s_lexbuf	*next;
	struct s_lexbuf	*prev;
	char			*value;
	char			**env;
	int				type;
	t_input			*input;
}					t_lexbuf;

// PROGRAM
int					main(int ac, char **av, char **env);

// INIT STRUCT
void				init_utils(t_utils *utils);
void				init_struct(t_input *input);
void				reset_iterators(t_utils *utils);

// FREE
void				ft_free(char *msg, t_lexbuf **tokens, int i);
void				ft_free_list(t_lexbuf **tokens);
void				ft_free_tab(char **value);
void				ft_free_str(char *s);
void				parse_error(char *msg, t_lexbuf **tokens, int leave,
						int exit);

// TEST
void				print_stack(t_lexbuf *tokens);
void				print_tab(char **strs);

// LEXING
char				*fill_tokens(char *s, int i, t_lexbuf **tokens);
int					token_type(char *s, int *i);
int					token_context(t_lexbuf **tokens);
int					token_check(t_lexbuf *tmp, t_lexbuf **tokens);
int					precise_token(t_lexbuf **tmp, t_lexbuf **tokens, int type);
void				small_check(t_lexbuf **tokens, int i);
void				quote_check(t_lexbuf **tokens);
void				big_check(char *s, int *size, t_lexbuf **tokens);
void				add_back(t_lexbuf **lst, t_lexbuf *new);
t_lexbuf			*new_tokens(char *s, int *i, t_input *input);
t_lexbuf			*token_recognition(char *s, t_input *input, int i,
						char **env);
t_lexbuf			*get_last(t_lexbuf *lst);
t_lexbuf			*ft_addprev(t_lexbuf *token);
t_lexbuf			*get_last(t_lexbuf *lst);
t_lexbuf			*parsing(t_input *input, char **env);

// EXPAND
char				*expand_heredoc(char *s, t_lexbuf **tokens, char **env);
char				*do_heredoc_expand(char *s, char **env, t_lexbuf **tokens,
						t_utils utils);
int					find_envar(char *arg, int i);
char				*get_varname(char *value, t_lexbuf **tokens, t_utils *utils,
						int j);
char				*get_varcontent(char *value, t_lexbuf **tokens,
						t_utils *utils, char *s);
char				*concatene_envar(char *value, char *envar,
						t_lexbuf **tokens, t_utils *utils);
char				*get_envar(char *value, char **env, t_lexbuf **tokens,
						t_utils *utils);
char				*expand_left(char *value, char *envar, t_lexbuf **tokens,
						t_utils *utils);
char				*expand_left_exit(char *value, char *envar,
						t_lexbuf **tokens, t_utils *utils);
char				*concatene_envar_exit(char *tokenvalue, char *envar,
						t_lexbuf **tokens, t_utils *utils);
void				expand(t_lexbuf **tokens, char **env);
void				do_expansion(t_lexbuf *tmp, t_lexbuf **tokens, char **env,
						t_utils *utils);
t_lexbuf			*create_tmp_list(char **new_strs, t_lexbuf *tmp,
						t_lexbuf **tokens, t_input *input);
t_lexbuf			*new_tokens_pexpand(char *s, int type, t_lexbuf **tokens,
						t_input *input);
t_lexbuf			*split_expands(t_lexbuf **tokens, t_input *input);
t_lexbuf			*remove_emptyexpands(t_lexbuf **tokens);

// QUOTES
int					quote_break(t_lexbuf **tokens, char *s, int *i);
char				*remove_quotes(char *src, t_lexbuf **tokens);
char				*ft_join_quotes(char *src, char *new_str, int len);
void				count_quotesrm(char *src, int *i, int *del);
void				quotes_removal(t_lexbuf **tokens);
void				skip_dquotes(t_utils *utils, char *src, int len,
						char *new_str);
void				skip_squotes(t_utils *utils, char *src, int len,
						char *new_str);
void				skip_check(char *value, int *i, int *inquote, char del);

// UTILS
int					is_space(char c);
int					ft_strncmpp(char *s1, char *s2, int n);
int					strncmp_env(char *s1, char *s2, int n);
int					is_indquote(char *s, t_utils *utils);
char				*mark_empty_expand(t_lexbuf **tokens);
void				negate_quotes(t_lexbuf **tokens);
void				skip(char *s, int *i, char del);
void				pos_quotes(t_lexbuf **tokens);
t_lexbuf			*copy_tokens(t_lexbuf **tokens, t_lexbuf *current);

// EXEC
// BUILTINS
// utils
char				*ft_strjoin2(char *s1, char *s2, char *s3, int checkfree);
int					check_path(char *path);
char				**cpy_env(char **env);
int					ft_strchr2(char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					find_equal(char *word);
int					strcmp_equal(char *env, char *arg);
int					is_only(char **arg, int ind);
int					ft_strcmp2(char *str1, char *str2);

char				**ft_cd(t_lexbuf *prompt, char **env);
char				*get_var_pwd(char **env, int check);
char				**ft_export_cd(char **env, char *pwd);
char				*trunc_path(char *oldpwd);

void				ft_echo(t_lexbuf *prompt);

int					check_env(char *arg, char **env);
void				free_env(char **env);
void				init_env_in_lex(t_lexbuf *prompt, char **env);
void				ft_env(t_lexbuf *prompt);

int					check_first_char(char *chaine);
int					nbr_inf(char **env, char *arg);
void				ft_export_noarg(char **env);
int					check_char(char *chaine);
int					*parse_export(char **arg, char **env);
char				**ft_export(t_lexbuf *prompt);
void				ft_export_child(t_lexbuf *prompt);
int					ft_export_parse_child(char **args, int *tab_nbr);

void				ft_exit(t_lexbuf *prompt);
void				write_error(t_lexbuf *prompt, char *s1,
						char *s2, int exit_status);

void				ft_pwd(void);

int					get_len_newenv(char **varname, char **env);
char				**ft_unset(t_lexbuf *prompt, char **env);

// PIPEX

void				pipex(t_lexbuf *prompt, int fd, int ind);
void				exit_error_no_cmd(t_lexbuf *prompt, int *tube, int fd);
void				exit_error_file(t_lexbuf *prompt, int *tube, int fd);
void				job(t_lexbuf *prompt, int *tube, char **env);
int					is_builtins(char *word);
char				**exec_builtins(t_lexbuf *prompt, char **env);
char				**ft_join_word(t_lexbuf *prompt, char **env);
char				*check_cmd(t_lexbuf *prompt, char **env, char *cmd);
void				free_split(char **r_split);
int					have_pipe(t_lexbuf *prompt);
t_lexbuf			*move_by_pipe(t_lexbuf *tokens);
int					is_directory(char *file);
char				**ft_join_word2(t_lexbuf *prompt);
int					number_of_args(t_lexbuf *prompt);
char				*extract_in_lexbuf(t_lexbuf *prompt, int type, int ind);
int					get_len_cmd(t_lexbuf *prompt);
int					args_is_in_env(char *var_env, char **args, int *tab_nbr);
int					ft_strlen_tab(char **str);
void				change_exit_status(int *exit_status, int error);
void				free_child(t_lexbuf *prompt);
int					ft_atoi(const char *nptr);
char				*ft_join_cmd(char *path, char *cmd);
int					check_path_in_env(char **env);
void				get_exit_status(t_lexbuf *prompt, pid_t pid, int status);
int					is_last_cmd(t_lexbuf *prompt);
int					is_last_in(t_lexbuf *prompt);
int					check_file(t_lexbuf *tokens);
int					get_output(t_lexbuf *prompt, int *tube);
int					get_infile(t_lexbuf *prompt, int *tube, int fd, int ind);
int					get_out(t_lexbuf *prompt);
int					get_in(t_lexbuf *prompt);
void				open_here_doc(t_lexbuf **prompt);
int					ft_here_doc(char *limiter, int *tube, char **env,
						t_lexbuf **tokens);
int					close_all_here_doc2(t_lexbuf *prompt);
void				add_here_doc(t_lexbuf *tmp, int *tube);
void				signal_pipex(int signum);
void				signal_readline2(int signum);
void				signal_readline(int signum);
void				signal_here_doc(int signum);

#endif
