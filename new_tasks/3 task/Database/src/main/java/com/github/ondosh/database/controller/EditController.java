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

    public void setGame(Game game) {
        if (game == null) return;
        this.originalGame = game;
        titleField.setText(game.getTitle());
        genreField.setText(game.getGenre());
        priceField.setText(String.valueOf(game.getPrice()));
        ratingField.setText(String.valueOf(game.getRating()));
    }

    public Game getResult() {
        return result;
    }

    public boolean isApproved() {
        return approved;
    }

    @FXML
    private void onSave() {
        // ParsedInput — вспомогательный record, чтобы вернуть сразу несколько значений
        // из validateAndParse() без дублирования парсинга
        ParsedInput input = validateAndParse();
        if (input == null) return;

        if (originalGame != null) {
            // Мутируем оригинальный объект напрямую — вызывающий код получит
            // изменения через свою же ссылку, даже не вызывая getResult()
            originalGame.setTitle(input.title());
            originalGame.setGenre(input.genre());
            originalGame.setPrice((float) input.price());
            originalGame.setRating((float) input.rating());
            // result намеренно указывает на тот же объект, что и originalGame —
            // это не копия, а одна и та же ссылка
            result = originalGame;
        } else {
            result = new Game(input.title(), input.genre(), (float) input.price(), (float) input.rating());
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
     * Валидирует поля и сразу парсит числа — один проход вместо двух.
     * Возвращает null если данные невалидны (Alert уже показан внутри).
     */
    private ParsedInput validateAndParse() {
        String title = titleField.getText().trim();
        String genre = genreField.getText().trim();
        String priceText = priceField.getText().trim();
        String ratingText = ratingField.getText().trim();

        if (title.isEmpty() || genre.isEmpty()) {
            showAlert("Название и жанр не могут быть пустыми");
            return null;
        }

        try {
            float price = Float.parseFloat(priceText);
            float rating = Float.parseFloat(ratingText);

            if (price < 0) {
                showAlert("Цена не может быть отрицательной");
                return null;
            }
            if (rating < 0 || rating > 10) {
                showAlert("Рейтинг должен быть от 0 до 10");
                return null;
            }


            return new ParsedInput(title, genre, price, rating);

        } catch (NumberFormatException e) {
            showAlert("Цена и рейтинг должны быть числами");
            return null;
        }
    }

    private void showAlert(String message) {
        Alert alert = new Alert(Alert.AlertType.WARNING);
        alert.setTitle("Ошибка");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    private void closeDialog() {
        Stage stage = (Stage) titleField.getScene().getWindow();
        stage.close();
    }

    // record — компактный способ передать несколько значений без отдельного класса.
    // Неизменяем: все поля final, equals/hashCode/toString генерируются автоматически
    private record ParsedInput(String title, String genre, double price, double rating) {}
}