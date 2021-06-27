# Memory crypt
Permet de chiffrer et de déchiffrer des fonctions directement depuis la mémoire RAM.

# Exemple d'usage
```cpp
void stub_function() { } // Fonction de stub

// Fonction malicieuse
void malicious_function()
{
	MessageBoxA(0, "Test", "Test", 0);
}

int main()
{
	DWORD func_size = process_size((DWORD*)&malicious_function, (DWORD*)&stub_function);

	// On initialise le client en chiffrant la fonction pour qu'elle soit illisible.
	memcrypt((DWORD)&malicious_function, func_size);
	// Désormais impossible d'executer `malicious_function()`.

	// TO DO: Attendre que le serveur envoi une commande au client qui demande d'executer la fonction `malicious_function()` ...

	// On déchiffre la fonction à executer (la même fonction pour chiffrer)
	memcrypt((DWORD)&malicious_function, func_size);

	// Il est désormais impossible d'executer la fonction.
	malicious_function();
	return 0;
}
```
