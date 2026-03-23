vim.g.mapleader = " "

vim.keymap.set("n", "<leader>ff", ":%!rustfmt<CR>", { silent = true })
vim.keymap.set("n", "<leader>fm", ":Explore<CR>", { silent = true })
vim.keymap.set("t", "<Esc>", [[<C-\><C-n>]])

vim.opt.clipboard = "unnamedplus"
vim.opt.mouse = "" -- or "a"
vim.opt.hlsearch = true
vim.opt.incsearch = true
vim.opt.ignorecase = true
vim.opt.smartcase = true

vim.opt.number = true
vim.opt.relativenumber = true
vim.opt.cursorline = true
vim.opt.wrap = false

vim.opt.tabstop = 4
vim.opt.shiftwidth = 4
vim.opt.expandtab = true
vim.opt.autoindent = true
vim.opt.smartindent = true

vim.api.nvim_create_autocmd("FileType", {
	pattern = { "cpp", "c", "objc", "objcpp" },
	callback = function(args)
		vim.lsp.start({
			name = "clangd",
			cmd = { "clangd", "--background-index", "--clang-tidy", "--log=error" },
			root_dir = vim.fs.dirname(
				vim.fs.find({ ".git", "compile_commands.json", "main.cpp" }, { upward = true })[1]
			) or vim.fn.expand("%:p:h"),
			capabilities = vim.lsp.protocol.make_client_capabilities(),
		})

		vim.api.nvim_create_autocmd("BufWritePre", {
			buffer = args.buf,
			callback = function()
				vim.lsp.buf.format({ async = false })
			end,
		})
	end,
})

vim.api.nvim_create_autocmd("LspAttach", {
	callback = function(args)
		local opts = { buffer = args.buf }
		vim.keymap.set("n", "<leader>lgd", vim.lsp.buf.definition, opts)
		vim.keymap.set("n", "<leader>lh", vim.lsp.buf.hover, opts)
		vim.keymap.set("n", "<leader>lr", vim.lsp.buf.rename, opts)
		vim.keymap.set("n", "<leader>le", vim.diagnostic.open_float, opts)
	end,
})

vim.diagnostic.config({
	virtual_text = true,
	signs = true,
	update_in_insert = false,
})

vim.opt.omnifunc = "v:lua.vim.lsp.omnifunc"
vim.opt.completeopt = { "menuone", "noselect", "noinsert" }
vim.opt.shortmess:append("c")
vim.keymap.set("i", "<Tab>", function()
	if vim.fn.pumvisible() == 1 then
		return "<C-n>"
	elseif
		vim.fn.col(".") > 1 and vim.fn.getline("."):sub(vim.fn.col(".") - 1, vim.fn.col(".") - 1):match("%s") == nil
	then
		return "<C-x><C-o>"
	else
		return "<Tab>"
	end
end, { expr = true, replace_keycodes = true })
vim.api.nvim_create_autocmd("TextChangedI", {
	callback = function()
		local line = vim.api.nvim_get_current_line()
		local col = vim.api.nvim_win_get_cursor(0)[2]

		local char = line:sub(col, col)
		if char:match("[%w%.%>]") then
			vim.fn.feedkeys(vim.api.nvim_replace_termcodes("<C-x><C-o>", true, true, true), "n")
		end
	end,
})
vim.keymap.set("i", "<CR>", function()
	if vim.fn.pumvisible() ~= 0 then
		return vim.fn.complete_info()["selected"] ~= -1 and "<C-y>" or "<C-e>"
	else
		return "<CR>"
	end
end, { expr = true, replace_keycodes = true })
