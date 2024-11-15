export class LoginRequestModel{
    username: string;
    password: string;
  
    constructor(jsonData?: any) {
      if (typeof jsonData == 'object') {
        this.username = jsonData['username'];
        this.password = jsonData['password'];
      } else {
        this.username = '';
        this.password = '';
      }
    }
  }
  