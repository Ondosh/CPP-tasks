package com.github.ondosh.database.controller;

import com.github.ondosh.database.model.Game;
import com.github.ondosh.database.service.GameService;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.io.IOException;

public class MainController {

    // Элементы из fxml
    @FXML private TableView<Game> gamesTable;
    @FXML private TableColumn<Game, String> titleColumn;
    @FXML private TableColumn<Game, String> genreColumn;
    @FXML private TableColumn<Game, Float> priceColumn;
    @FXML private TableColumn<Game, Float> ratingColumn;
    @FXML private ComboBox<String> sortComboBox;
    @FXML private Label statusLabel;


    @FXML private TextField searchField;

    // Храним ВСЕ игры отдельно от отфильтрованных
    // Данные хранятся здесь, не в таблице
    // Это и есть использование шаблона наблюдатель
    // Наблюдаемый объект тоже может наблюдать
    private final ObservableList<Game> allGames = FXCollections.observableArrayList();
    private final ObservableList<Game> gamesList = FXCollections.observableArrayList();

    private final GameService gameService = new GameService();

    /**
     * Вызывается автоматически при запуске — инициализация таблицы
     */
    @FXML
    public void initialize() {
        // Привязываем колонки к полям класса Game
        // Если не title, а title123, то колонка titleColumn, то она ищет геттеры и сеттеры
        // с названием getTitle23 и setTitle123.
        titleColumn.setCellValueFactory(new PropertyValueFactory<Game, String>("title"));
        genreColumn.setCellValueFactory(new PropertyValueFactory<Game, String>("genre"));
        priceColumn.setCellValueFactory(new PropertyValueFactory<Game, Float>("price"));
        ratingColumn.setCellValueFactory(new PropertyValueFactory<Game, Float>("rating"));

        // Привязываем список к таблице
        // gamesTable - наблюдатель, gamesList - наблюдаемый
        // Может и наоборот
        gamesTable.setItems(gamesList);

        // Заполняем выпадающий список сортировки
        sortComboBox.setItems(FXCollections.observableArrayList(
                "Название", "Жанр", "Цена", "Рейтинг"
        ));

        // Загружаем данные из БД
        loadGames();
    }

    /**
     * Загружает все игры из БД в список
     */
    private void loadGames() {
        allGames.clear();
        allGames.addAll(gameService.getAllGames()); // было gameDAO
        applyFilters();
        statusLabel.setText("Загружено игр: " + allGames.size());
    }

    /**
     * Фильтрует gamesList по поисковому запросу и применяет сортировку
     */
    private void applyFilters() {
        String query = searchField.getText().trim().toLowerCase();

        // Фильтрация по названию (частичное совпадение, регистронезависимо)
        ObservableList<Game> filtered = allGames.filtered(game ->
                query.isEmpty() || game.getTitle().toLowerCase().contains(query)
        );

        // Сортировка, если выбрана
        String sortField = sortComboBox.getValue();
        if (sortField != null && !sortField.isEmpty()) {
            filtered = FXCollections.observableArrayList(filtered);
            filtered.sort((g1, g2) -> {
                return switch (sortField) {
                    case "Название" -> g1.getTitle().compareToIgnoreCase(g2.getTitle());
                    case "Жанр"     -> g1.getGenre().compareToIgnoreCase(g2.getGenre());
                    case "Цена"     -> Float.compare(g1.getPrice(), g2.getPrice());
                    case "Рейтинг"  -> Float.compare(g2.getRating(), g1.getRating());
                    default -> 0;
                };
            });
        }

        // Обновляем отображаемый список
        gamesList.setAll(filtered);

        // Обновляем статус
        if (!query.isEmpty()) {
            statusLabel.setText("Найдено: " + filtered.size() + " из " + allGames.size());
        }
    }

    /**
     * Нажатие кнопки Добавить
     */
    @FXML
    private void onAddButton() {
        Game editedGame = showDialog(null);
        if (editedGame != null) {
            gameService.addGame(editedGame); // было gameDAO
            allGames.add(editedGame);
            applyFilters();
            statusLabel.setText("Добавлена игра: " + editedGame.getTitle());
        }
    }


    @FXML
    private void onEditButton() {
        Game selected = gamesTable.getSelectionModel().getSelectedItem();
        if (selected == null) {
            statusLabel.setText("Выберите игру для изменения");
            return;
        }
        Game editedGame = showDialog(selected);
        if (editedGame != null) {
            gameService.updateGame(editedGame, editedGame.getId()); // было gameDAO
            int index = allGames.indexOf(selected);
            if (index >= 0) allGames.set(index, editedGame);
            applyFilters();
            statusLabel.setText("Изменена игра: " + editedGame.getTitle());
        }
    }

    @FXML
    private void onDeleteButton() {
        Game selected = gamesTable.getSelectionModel().getSelectedItem();
        if (selected == null) {
            statusLabel.setText("Выберите игру для удаления");
            return;
        }
        gameService.deleteGame(selected.getId()); // было gameDAO
        allGames.remove(selected);
        applyFilters();
        statusLabel.setText("Игра удалена: " + selected.getTitle());
    }
    /**
     * Открывает диалоговое окно добавления/редактирования
     * @param game игра для редактирования, или null для создания новой
     * @return изменённый/новый объект Game, или null если отменено
     */
    private Game showDialog(Game game) {
        try {
            FXMLLoader loader = new FXMLLoader(
                    getClass().getResource("/com/github/ondosh/database/edit.fxml")
            );
            Parent root = loader.load();

            EditController controller = loader.getController();
            if (game != null) {
                controller.setGame(game);
            }

            Stage stage = new Stage();
            stage.setTitle(game == null ? "Добавить игру" : "Изменить игру");
            stage.setScene(new Scene(root));
            stage.setResizable(false);
            stage.initModality(Modality.WINDOW_MODAL);
            stage.initOwner(gamesTable.getScene().getWindow());
            stage.showAndWait();

            return controller.isApproved() ? controller.getResult() : null;

        } catch (IOException e) {
            e.printStackTrace();
            statusLabel.setText("Ошибка загрузки окна");
            return null;
        }
    }

    @FXML
    private void onSortChanged() {
        applyFilters(); // пересортирует уже отфильтрованный список
        String field = sortComboBox.getValue();
        if (field != null && searchField.getText().trim().isEmpty()) {
            statusLabel.setText("Сортировка по: " + field);
        }
    }

    @FXML
    private void onSearchChanged() {
        applyFilters();
    }

    @FXML
    private void onSearchClear() {
        searchField.clear();
        applyFilters();
        searchField.requestFocus();
    }
}