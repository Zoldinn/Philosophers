CC = cc
FLAGS = -Wall -Werror -Wextra -pthread -g
NAME = philo

# Dossiers
SRC_DIR = srcs
OBJ_DIR = objs

# Fichiers sources
SRC = end.c \
	errors_handler.c \
	init.c \
	philo.c \
	routine.c \
	utils_func.c \
	utils_philo.c

# Ajout des préfixes de dossiers
SRC := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Cible principale
all: banner $(NAME)

banner:
	@cat banner.txt
	@echo "\n"

# Compilation de l'exécutable
$(NAME): $(OBJ)
	@echo "🔨 Compiling ..."
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "✅ \e[32mCompiled successfully!\e[0m\n"

# Compilation des fichiers objets dans OBJ_DIR
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "🔧 Compiling $<..."
	@$(CC) $(FLAGS) -c $< -o $@

# Création du dossier OBJ_DIR si nécessaire
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Nettoyage des fichiers objets et du dossier OBJ_DIR
clean:
	@echo "🧹 \e[33mCleaning .o of $(NAME)...\e[0m"
	@rm -rf $(OBJ_DIR)

# Nettoyage complet
fclean: clean
	@echo "🗑️ \e[33m Deleting $(NAME) ...\e[0m"
	@rm -f $(NAME)

# Rebuild complet
re: fclean all
