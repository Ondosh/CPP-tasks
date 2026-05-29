package com.github.ondosh.database.controller;

import com.github.ondosh.database.model.Game;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class EditController {

    @FXML private TextField titleField;
    @FXML private TextField genreField;
    @FXML private TextField priceField;
    @FXML private TextField ratingField;

    // Лэйблы предупреждений под каждым полем
    @FXML private Label titleError;
    @FXML private Label genreError;
    @FXML private Label priceError;
    @FXML private Label ratingError;

    private Game result;
    private boolean approved = false;
    private Game originalGame;

    private static final String ERROR_STYLE =
            "-fx-border-color: #e53935; -fx-border-width: 1.5px; -fx-border-radius: 3px;";

    public void setGame(Game game) {
        if (game == null) return;
        this.originalGame = game;
        titleField.setText(game.getTitle());
        genreField.setText(game.getGenre());
        priceField.setText(String.valueOf(game.getPrice()));
        ratingField.setText(String.valueOf(game.getRating()));
    }

    @FXML
    public void initialize() {
        // Снимаем подсветку как только пользователь начинает редактировать поле
        titleField.textProperty().addListener((obs, o, n) -> clearError(titleField, titleError));
        genreField.textProperty().addListener((obs, o, n) -> clearError(genreField, genreError));
        priceField.textProperty().addListener((obs, o, n) -> clearError(priceField, priceError));
        ratingField.textProperty().addListener((obs, o, n) -> clearError(ratingField, ratingError));
    }

    public Game getResult() { return result; }
    public boolean isApproved() { return approved; }

    @FXML
    private void onSave() {
        ParsedInput input = validateAndParse();
        if (input == null) return;

        if (originalGame != null) {
            originalGame.setTitle(input.title());
            originalGame.setGenre(input.genre());
            originalGame.setPrice((float) input.price());
            originalGame.setRating((float) input.rating());
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
     * Валидирует все поля сразу, выставляя подсветку и сообщения.
     * Возвращает null если хотя бы одно поле невалидно.
     */
    private ParsedInput validateAndParse() {
        clearAllErrors();

        String title  = titleField.getText().trim();
        String genre  = genreField.getText().trim();
        String priceText  = priceField.getText().trim();
        String ratingText = ratingField.getText().trim();

        boolean valid = true;

        if (title.isEmpty()) {
            setError(titleField, titleError, "Название не может быть пустым");
            valid = false;
        }
        if (genre.isEmpty()) {
            setError(genreField, genreError, "Жанр не может быть пустым");
            valid = false;
        }

        float price = 0, rating = 0;

        try {
            price = Float.parseFloat(priceText);
            if (price < 0) {
                setError(priceField, priceError, "Цена не может быть отрицательной");
                valid = false;
            }
        } catch (NumberFormatException e) {
            setError(priceField, priceError, "Введите корректное число");
            valid = false;
        }

        try {
            rating = Float.parseFloat(ratingText);
            if (rating < 0 || rating > 10) {
                setError(ratingField, ratingError, "Рейтинг должен быть от 0 до 10");
                valid = false;
            }
        } catch (NumberFormatException e) {
            setError(ratingField, ratingError, "Введите корректное число");
            valid = false;
        }

        return valid ? new ParsedInput(title, genre, price, rating) : null;
    }

    private void setError(TextField field, Label errorLabel, String message) {
        field.setStyle(ERROR_STYLE);
        errorLabel.setText(message);
        errorLabel.setVisible(true);
        errorLabel.setManaged(true);
    }

    private void clearError(TextField field, Label errorLabel) {
        field.setStyle("");
        errorLabel.setVisible(false);
        errorLabel.setManaged(false);
    }

    private void clearAllErrors() {
        clearError(titleField,  titleError);
        clearError(genreField,  genreError);
        clearError(priceField,  priceError);
        clearError(ratingField, ratingError);
    }

    private void closeDialog() {
        Stage stage = (Stage) titleField.getScene().getWindow();
        stage.close();
    }

    private record ParsedInput(String title, String genre, double price, double rating) {}
}