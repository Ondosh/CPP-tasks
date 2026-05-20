package com.github.ondosh.database.controller;

import com.github.ondosh.database.model.Game;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class EditController {

    @FXML private TextField titleField;
    @FXML private TextField genreField;
    @FXML private TextField priceField;
    @FXML private TextField ratingField;

    private Game result;
    private boolean approved = false;
    private Game originalGame;
    /**
     * Заполняет поля данными существующей игры (для редактирования)
     */
    public void setGame(Game game) {
        if (game == null) return;
        this.originalGame = game; // запоминаем
        titleField.setText(game.getTitle());
        genreField.setText(game.getGenre());
        priceField.setText(String.valueOf(game.getPrice()));
        ratingField.setText(String.valueOf(game.getRating()));
    }

    /**
     * Возвращает созданную/изменённую игру
     */
    public Game getResult() {
        return result;
    }

    /**
     * Проверяет, нажал ли пользователь "Сохранить"
     */
    public boolean isApproved() {
        return approved;
    }

    @FXML
    private void onSave() {
        if (!validateInput()) return;

        String title = titleField.getText().trim();
        String genre = genreField.getText().trim();
        float price = Float.parseFloat(priceField.getText().trim());
        float rating = Float.parseFloat(ratingField.getText().trim());

        if (originalGame != null) {
            // Редактирование — обновляем существующий объект
            originalGame.setTitle(title);
            originalGame.setGenre(genre);
            originalGame.setPrice(price);
            originalGame.setRating(rating);
            result = originalGame;
        } else {
            // Создание нового
            result = new Game(title, genre, price, rating);
        }

        approved = true;
        closeDialog();
    }

    @FXML
    private void onCancel() {
        approved = false;
        closeDialog();
    }

    /**
     * Валидация введённых данных
     */
    private boolean validateInput() {
        String title = titleField.getText().trim();
        String genre = genreField.getText().trim();
        String priceText = priceField.getText().trim();
        String ratingText = ratingField.getText().trim();

        if (title.isEmpty() || genre.isEmpty()) {
            showAlert("Ошибка", "Название и жанр не могут быть пустыми");
            return false;
        }

        try {
            float price = Float.parseFloat(priceText);
            float rating = Float.parseFloat(ratingText);

            if (price < 0) {
                showAlert("Ошибка", "Цена не может быть отрицательной");
                return false;
            }
            if (rating < 0 || rating > 10) {
                showAlert("Ошибка", "Рейтинг должен быть от 0 до 10");
                return false;
            }
        } catch (NumberFormatException e) {
            showAlert("Ошибка", "Цена и рейтинг должны быть числами");
            return false;
        }

        return true;
    }

    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.WARNING);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    private void closeDialog() {
        Stage stage = (Stage) titleField.getScene().getWindow();
        stage.close();
    }
}