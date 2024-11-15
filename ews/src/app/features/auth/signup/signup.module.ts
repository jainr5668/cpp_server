import { CommonModule } from '@angular/common';
import { NgModule } from '@angular/core';
import { TranslateModule } from "@ngx-translate/core";
import { SignupRoutingModule } from './signup.routing.module';
import { CardModule } from '@patterns/card';
import { SignupComponent } from './signup.component';

@NgModule({
  declarations: [SignupComponent],
  imports: [
    CardModule,
    CommonModule,
    TranslateModule,
    SignupRoutingModule
  ],
  exports: [SignupComponent],
})
export class SignupModule {}
