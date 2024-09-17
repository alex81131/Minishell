int	set_env_var_2(t_env **env, t_env *var, char *id, char *new_value, char *tmp)
{
	t_env	*new;

	if (var)
	{
		free(var->value);
		var->value = new_value;
		free(var->sum);
		var->sum = tmp;
	}
	else
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			return (EXIT_FAILURE);
		new->id = ft_strdup(id);
		if (!new->id)
			return (free(new), EXIT_FAILURE);
		new->value = new_value;
		new->sum = tmp;
		new->next = NULL;
		env_var_add(env, new);
	}
	return (EXIT_SUCCESS);
}

int	set_env_var(t_env **env, char *id, char *value)
{
	t_env	*var;
	char	*new_value;
	char	*tmp;

	new_value = ft_strdup(value);
	if (!new_value)
		return (EXIT_FAILURE);
	tmp = ft_strjoin(id, "=");
	if (!tmp)
		return (free(new_value), EXIT_FAILURE);
	tmp = ps_strjoin(tmp, value);
	if (!tmp)
		return (free(new_value), EXIT_FAILURE);
	var = get_env_var(*env, id);
	if (set_env_var_2(env, var, id, new_value, tmp))
		return (free(new_value), free(tmp), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
