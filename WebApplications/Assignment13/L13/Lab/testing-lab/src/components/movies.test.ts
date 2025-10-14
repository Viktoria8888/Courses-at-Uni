
import { describe, it, expect, beforeEach, afterEach, vi } from "vitest";
import { screen } from "@testing-library/dom";
import userEvent from "@testing-library/user-event";
import { setupMovies } from "./movies";
import "@testing-library/jest-dom/vitest";

describe("setupMovies (integration)", () => {
    let container: HTMLElement;
    beforeEach(() => {
        container = document.createElement("div");
        document.body.appendChild(container);
        vi.clearAllMocks();
    });
    afterEach(() => {
        document.body.innerHTML = "";
    });

    it("renders add movie form", () => {
        setupMovies(container);
        expect(screen.getByPlaceholderText("Movie Title")).toBeInTheDocument();
        expect(screen.getByPlaceholderText("Release Year")).toBeInTheDocument();
        expect(screen.getByText("Add Movie")).toBeInTheDocument();
    });




    it("removes a movie when remove button is clicked", async () => {
        setupMovies(container);

        await userEvent.type(screen.getByPlaceholderText("Movie Title"), "Test Movie");
        await userEvent.type(screen.getByPlaceholderText("Release Year"), "2020");
        await userEvent.click(screen.getByText("Add Movie"));

        await userEvent.click(screen.getByText("Remove"));
        expect(screen.queryByText("Test Movie (2020)")).not.toBeInTheDocument();
    });

});