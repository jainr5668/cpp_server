import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { TranslateModule } from '@ngx-translate/core';
import { LoginComponentRoutingModule } from './login.component.routing.module';
import { CardModule } from '@patterns/card';
import { LoginComponent } from './login.component';
import { AuthService } from '@utills/auth';

@NgModule({
  declarations: [LoginComponent],
  imports: [CardModule, CommonModule, TranslateModule, LoginComponentRoutingModule],
  exports: [LoginComponent],
  providers: [
    AuthService
  ]
})
export class LoginModule {}
