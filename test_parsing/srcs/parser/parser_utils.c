/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbocquel <mbocquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:50:05 by mbocquel          #+#    #+#             */
/*   Updated: 2023/03/06 18:28:38 by mbocquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

/*Voir le cas ou on a pas de quote mais directement un changement
de variable*/
char	*get_word(t_param *prm)
{
	t_token	peek;
	char	*token;

	peek = peek_tk(prm);
	if (!(peek == TK_WORD || peek == TK_SQUOTE || peek == TK_DQUOTE || peek == TK_DOLLAR))
		return (NULL);
	token = get_token(prm);
	if (get_t_token(token) == TK_WORD)
		return (token);
	if (get_t_token(token) == TK_SQUOTE)
		return (get_word_squote(prm));
	if (get_t_token(token) == TK_DQUOTE)
		return (get_word_dquote(prm));
	if (get_t_token(token) == TK_DOLLAR)
		return (get_word_dollar(prm));
	return (NULL);
}

char	*get_word_squote(t_param *prm)
{
	char	*word;
	size_t	pos_start;

	word = NULL;
	pos_start = prm->source.cur;
	while (peek_tk(prm) != TK_SQUOTE && peek_tk(prm) != TK_EOF)
		get_token(prm);
	if (peek_tk(prm) == TK_EOF)
	{
		prm->source.error = ERR_SQUOTE_CLOSE;
		return (NULL);
	}
	if (peek_tk(prm) == TK_SQUOTE)
		get_token(prm);
	word = ft_substr_gc(prm, prm->source.line, pos_start,
			prm->source.cur - pos_start - 1);
	return (word);
}

char	*get_word_dquote(t_param *prm)
{
	char	*word;
	int		pos_start;
	int		pos_end;
	char	*to_process;

	word = NULL;
	pos_start = (int)prm->source.cur;
	pos_end = pos_start + get_pos_in_str(prm->source.line + pos_start, '\"');
	if (pos_end - pos_start == -1)
	{
		prm->source.error = ERR_DQUOTE_CLOSE;
		return (NULL);
	}
	to_process = ft_substr_gc(prm, prm->source.line, pos_start,
			pos_end - pos_start);
	while (get_pos_in_str(to_process, '$') != -1)
		get_word_dquote_2(prm, &to_process, &pos_start, &word);
	if (get_pos_in_str(to_process, '$') == -1)
		word = ft_strjoin_gc(prm, prm->source.id, word, to_process);
	prm->source.cur = pos_end + 1;
	return (word);
}

void	get_word_dquote_2(t_param *prm, char **to_process,
	int *pos_start, char **word)
{
	char	*var_sub;

	*word = ft_strjoin_gc(prm, prm->source.id, *word,
			ft_substr_gc(prm, *to_process, 0,
				get_pos_in_str(*to_process, '$')));
	prm->source.cur = *pos_start + get_pos_in_str(*to_process, '$');
	get_token(prm);
	if (ft_isspace(prm->source.line[prm->source.cur]))
		var_sub = "$";
	else
		var_sub = get_token(prm);
	*pos_start = prm->source.cur;
	*word = ft_strjoin_gc(prm, prm->source.id, *word,
			get_env_var(prm, var_sub));
	*to_process = ft_substr_gc(prm, prm->source.line, *pos_start,
			get_pos_in_str(prm->source.line + *pos_start, '\"'));
}

char	*get_word_dollar(t_param *prm)
{
	char	*var_sub;

	if (peek_tk(prm) != TK_WORD)
		return ("$");
	var_sub = get_token(prm);
	return (get_env_var(prm, var_sub));	
}

char	*get_space(t_param *prm);

char	*substitute_word(t_param *prm, char	*word)
{
	char	*new_word;
	int		pos_dol;
	int		len_var_sub;
	char	*var_sub;
	char 	*to_process;

	new_word = NULL;
	if (word == NULL)
		return (NULL);
	pos_dol = get_pos_in_str(word, '$');
	if (pos_dol == -1)
		return (word);
	else
	{
		new_word = ft_strjoin_gc(prm, prm->source.id, new_word,
			ft_substr_gc(prm, word, 0, pos_dol));
		if (pos_dol + 1 == (int)ft_strlen(word))//le $est sur la fin
			new_word = ft_strjoin_gc(prm, prm->source.id, new_word, "$");
		else
		{
			len_var_sub = ft_strlen(word) - pos_dol	- 1;
			if (get_pos_in_str(word + pos_dol + 1, '$') != -1)
				len_var_sub = get_pos_in_str(word + pos_dol + 1, '$');
			
			var_sub = ft_substr_gc(prm, word, pos_dol + 1, len_var_sub);
			//printf("	var_sub %s\n", var_sub);
			new_word = ft_strjoin_gc(prm, prm->source.id, new_word, get_env_var(prm, var_sub));
			to_process = ft_substr_gc(prm, word, pos_dol + 1 + len_var_sub, ft_strlen(word));
			if (ft_strlen(to_process))
				new_word = ft_strjoin_gc(prm, prm->source.id, new_word, substitute_word(prm,to_process));
			//printf("	to_process %s\n", to_process);
		}
	}
	return (new_word);
}
