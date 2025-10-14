import { describe, it, expect, beforeEach, afterEach, vi } from "vitest";
import {
    validateMovie,
    sortMoviesByYear,
    movieReducer,
    formatMovie,
} from "./helpers";
import type { MovieType, MovieAction } from "../types/Movie.types";


vi.mock("nanoid", () => ({
    nanoid: () => "test-id",
}));

describe("validateMovie tests", () => {
    const existingMovies: MovieType[] = [
        {
            id: "1",
            title: "Inception",
            year: 2010,
            createdAt: new Date("2020-01-01"),
        },
    ];

    it("should return error if title is empty", () => {
        const errors = validateMovie({ title: "", year: 2010 }, []);
        expect(errors).toContain("Title is required");
    });

    it("should return error if title is too short", () => {
        const errors = validateMovie({ title: "A", year: 2010 }, []);
        expect(errors).toContain("Title is too short");
    });

    it("should return error if title contains invalid characters", () => {
        const errors = validateMovie({ title: "Bad@Title!", year: 2010 }, []);
        expect(errors).toContain("Title contains invalid characters");
    });

    it("should return error if year is not a number", () => {
        // @ts-expect-error
        const errors = validateMovie({ title: "Valid", year: "not-a-number" }, []);
        expect(errors).toContain("Year must be a number");
    });

    it("should return error if year is less than 1888", () => {
        const errors = validateMovie({ title: "Old Movie", year: 1800 }, []);
        expect(errors).toContain("Year must be 1888 or later");
    });

    it("should return error if movie already exists", () => {
        const errors = validateMovie(
            { title: "Inception", year: 2010 },
            existingMovies
        );
        expect(errors).toContain("This movie already exists");
    });

    it("should return no errors for valid movie", () => {
        const errors = validateMovie(
            { title: "Interstellar", year: 2014 },
            existingMovies
        );
        expect(errors).toEqual([]);
    });
});

describe("sortMoviesByYear tests", () => {
    const movies: MovieType[] = [
        { id: "1", title: "Movie A", year: 2000, createdAt: new Date("2020-01-01") },
        { id: "2", title: "Movie B", year: 1990, createdAt: new Date("2020-01-02") },
        { id: "3", title: "Movie C", year: 2010, createdAt: new Date("2020-01-03") },
    ];

    it("should sort movies by year ascending", () => {
        const sorted = sortMoviesByYear(movies, true);
        expect(sorted.map((m) => m.year)).toEqual([1990, 2000, 2010]);
    });

    it("should sort movies by year descending", () => {
        const sorted = sortMoviesByYear(movies, false);
        expect(sorted.map((m) => m.year)).toEqual([2010, 2000, 1990]);
    });
});

describe("movieReducer tests", () => {
    beforeEach(() => {
        vi.useFakeTimers();
        vi.setSystemTime(new Date("2024-01-01T00:00:00Z"));
    });
    afterEach(() => {
        vi.useRealTimers();
    });

    it("should add a movie on ADD_MOVIE", () => {
        const initialState: MovieType[] = [];
        const action: MovieAction = {
            type: "ADD_MOVIE",
            payload: { title: "Tenet", year: 2020 },
        };
        const newState = movieReducer(initialState, action);
        expect(newState).toHaveLength(1);
        expect(newState[0]).toMatchObject({
            id: "test-id",
            title: "Tenet",
            year: 2020,
        });
        expect(newState[0].createdAt).toEqual(new Date("2024-01-01T00:00:00Z"));
    });

    it("should remove a movie on REMOVE_MOVIE", () => {
        const initialState: MovieType[] = [
            {
                id: "1",
                title: "Movie 1",
                year: 2000,
                createdAt: new Date("2020-01-01"),
            },
            {
                id: "2",
                title: "Movie 2",
                year: 2010,
                createdAt: new Date("2020-01-02"),
            },
        ];
        const action: MovieAction = { type: "REMOVE_MOVIE", payload: "1" };
        const newState = movieReducer(initialState, action);
        expect(newState).toHaveLength(1);
        expect(newState[0].id).toBe("2");
    });
});

describe("formatMovie tests", () => {
    it("should format movie correctly", () => {
        const movie: MovieType = {
            id: "1",
            title: "Dunkirk",
            year: 2017,
            createdAt: new Date("2022-05-10T12:00:00Z"),
        };
        const formatted = formatMovie(movie);
        expect(formatted).toBe("Dunkirk (2017) — Added on 2022-05-10");
    });
});