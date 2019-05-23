-- phpMyAdmin SQL Dump
-- version 4.7.0
-- https://www.phpmyadmin.net/
--
-- Värd: 127.0.0.1
-- Tid vid skapande: 24 sep 2017 kl 11:43
-- Serverversion: 10.1.26-MariaDB
-- PHP-version: 7.1.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Databas: `mastermind`
--

-- --------------------------------------------------------

--
-- Tabellstruktur `highscores`
--

CREATE TABLE `highscores` (
  `id` int(11) NOT NULL,
  `name` text CHARACTER SET utf8 COLLATE utf8_swedish_ci,
  `score` int(11) DEFAULT '0',
  `timestamp` timestamp NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumpning av Data i tabell `highscores`
--

INSERT INTO `highscores` (`id`, `name`, `score`, `timestamp`) VALUES
(1, 'Fredrik Engstrand', 13371337, '2017-09-15 08:24:37'),
(2, 'Johnnyponken', 420, '2017-09-15 09:09:20'),
(3, 'Kenny', 696969, '2017-09-15 09:31:05'),
(4, 'Lasse', 120, '2017-09-15 10:11:17'),
(5, 'Marrethegamer', 696970, '2017-09-15 10:30:26');

--
-- Index för dumpade tabeller
--

--
-- Index för tabell `highscores`
--
ALTER TABLE `highscores`
  ADD UNIQUE KEY `id` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
