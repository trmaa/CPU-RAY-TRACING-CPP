import express from 'express';
import path from 'path';
import { fileURLToPath } from 'url';

let PORT = process.env.PORT || 3000;

let APP = express();

let __filename = fileURLToPath(import.meta.url);
let __dirname = path.dirname(__filename);

APP.use(express.static(path.join(__dirname, './')));

APP.get('/', (res) => {
    res.sendFile(path.join(__dirname, './', 'index.html'));
});

APP.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
