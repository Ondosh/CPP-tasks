package com.github.ondosh.chatbot.bot;

import com.github.ondosh.chatbot.model.UserProfile;

/**
 * Основной интерфейс для всех реализаций ботов в системе.
 * <p>
 * Относится к модели проекта согласно архитектурному паттерну MVC.
 * Определяет контракт для взаимодействия с различными типами ботов:
 * простые боты-парсеры, боты на основе нейросетей, гибридные реализации и т.д.
 * </p>
 *
 * <h2>Особенности интерфейса:</h2>
 * <ul>
 *   <li>Использует методы {@code default} для предоставления базовой реализации
 *       большинства методов, что позволяет новым реализациям переопределять
 *       только необходимый функционал.</li>
 *   <li>Обязательным для реализации является только метод {@link #getResponse(String)}
 *       и методы управления статистикой ({@link #setStats(int, int, int)},
 *       {@link #getTotalMessages()}, {@link #getUserMessages()}, {@link #getBotMessages()}).</li>
 *   <li>Поддерживает персонализацию через {@link UserProfile}.</li>
 *   <li>Включает механизм отслеживания статистики сообщений для анализа
 *       активности и сохранения сессий.</li>
 * </ul>
 *
 * <h2>Типичный сценарий использования:</h2>
 * <pre>
 * IBot bot = new HybridBot();
 * bot.setUserProfile(profile);
 *
 * // Отправка сообщения
 * String reply = bot.getResponse("Привет, как дела?");
 * bot.countUserMessage();
 * bot.countBotMessage();
 *
 * // Сохранение статистики
 * int total = bot.getTotalMessages();
 * int user = bot.getUserMessages();
 * int bot = bot.getBotMessages();
 *
 * // Восстановление статистики при следующем запуске
 * bot.setStats(savedTotal, savedUser, savedBot);
 * </pre>
 *
 * <h2>Реализации:</h2>
 * <ul>
 *   <li>{@link SimpleBot} - простой бот с поддержкой команд и заготовленных фраз</li>
 *   <li>{@link GigaChatBot} - бот на основе нейросети GigaChat</li>
 *   <li>{@link HybridBot} - гибридный бот, комбинирующий SimpleBot и GigaChatBot</li>
 * </ul>
 *
 * @author ondosh
 * @version 1.0
 * @see UserProfile
 * @see SimpleBot
 * @see GigaChatBot
 * @see HybridBot
 */
public interface IBot {

    /** Возвращает ответ на сообщение пользователя. */
    String getResponse(String input);

    /** Возвращает имя/идентификатор бота. */
    default String getBotName() {
        return "Bot";
    }
    // default - делает реализацию "по умолчанию", тем самым добавляя её прямо в интерфейс
    /** Проверяет доступность бота. */
    default boolean isAvailable() {
        return true;
    }

    /** Учитывает сообщение пользователя в статистике. */
    default void countUserMessage() {}

    /** Учитывает ответ бота в статистике. */
    default void countBotMessage() {}

    /** Устанавливает профиль пользователя для персонализации. */
    default void setUserProfile(UserProfile profile) {}
    /**
     * Устанавливает статистику сообщений бота.
     * Используется для восстановления сохранённой статистики при загрузке профиля.
     *
     * @param stat  общее количество сообщений (пользователь + бот)
     * @param stat1 количество сообщений, отправленных пользователем
     * @param stat2 количество сообщений, отправленных ботом
     */
    void setStats(int stat, int stat1, int stat2);

    /**
     * Возвращает общее количество сообщений в текущей сессии.
     * Включает как сообщения пользователя, так и ответы бота.
     *
     * @return общее количество сообщений
     */
    int getTotalMessages();

    /**
     * Возвращает количество сообщений, отправленных пользователем.
     * Используется для анализа активности пользователя и сохранения статистики.
     *
     * @return количество пользовательских сообщений
     */
    int getUserMessages();

    /**
     * Возвращает количество сообщений, отправленных ботом.
     * Используется для анализа активности бота и сохранения статистики.
     *
     * @return количество сообщений бота
     */
    int getBotMessages();
}